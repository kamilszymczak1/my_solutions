#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1 << 25;

struct seg_tree_add_max {
    struct Node {
        int value, index;
        int lazy;
        Node() : lazy(0), value(inf), index(0) {}
        Node(int _value, int _index) : lazy(0), value(_value), index(_index) {}
    };
    Node merge(Node &l, Node &r) {
        Node ret = r;
        if(l.value < r.value)
            ret = l;
        ret.lazy = 0;
        return ret;
    }
    
    vector<Node>nodes;
    int leaf_count;
    
    seg_tree_add_max(vector<int>&a) {
        int n = a.size();
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        nodes.resize(leaf_count * 2);
        for(int i = 0; i < n; i++)
            nodes[i + leaf_count] = Node(a[i], i);
        for(int i = n; i < leaf_count; i++)
            nodes[i + leaf_count] = Node(inf, i);
        for(int i = leaf_count - 1; i > 0; i--)
            nodes[i] = merge(nodes[i * 2], nodes[i * 2 + 1]);
    }
    void propagate(int x) {
        for(int i = 0; i < 2; i++) {
            nodes[x * 2 + i].value += nodes[x].lazy;
            nodes[x * 2 + i].lazy += nodes[x].lazy;
        }
        nodes[x].lazy = 0;
    }
    void add(int a, int b, int value) { add(a, b + 1, 0, leaf_count, 1, value); }
    void add(int a, int b, int lo, int hi, int v, int value) {
        if(a == lo && b == hi) {
            nodes[v].lazy += value;
            nodes[v].value += value;
            return;
        }
        if(a >= b)
            return;
        propagate(v);
        int mid = (lo + hi) / 2;
        add(a, min(b, mid), lo, mid, v * 2, value);
        add(max(a, mid), b, mid, hi, v * 2 + 1, value);
        
        nodes[v] = merge(nodes[v * 2], nodes[v * 2 + 1]);
    }
    
    pair<int, int> get_min(int a, int b) {
        Node n = get_min(a, b + 1, 0, leaf_count, 1);
        return make_pair(n.value, n.index);
    }
    Node get_min(int a, int b, int lo, int hi, int v) {
        if(a == lo && b == hi)
            return nodes[v];
        if(a >= b)
            return Node(inf, 0);
        propagate(v);
        const int mid = (lo + hi) / 2;
        auto L = get_min(a, min(b, mid), lo, mid, v * 2);
        auto R = get_min(max(a, mid), b, mid, hi, v * 2 + 1);
        return merge(L, R);
    }
};

struct seg_tree_add_sum {
    vector<int>values;
    int leaf_count;
    seg_tree_add_sum(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values.resize(leaf_count * 2);
    }
    
    void add(int x, int value) {
        for(x += leaf_count; x; x /= 2)
            values[x] += value;
    }
    int get_sum(int a, int b) {
        a += leaf_count; b += leaf_count;
        int result = values[a];
        if(a != b)
            result += values[b];
        for(; a / 2 != b / 2; a /= 2, b /= 2) {
            if(a % 2 == 0)
                result += values[a + 1];
            if(b % 2 == 1)
                result += values[b - 1];
        }
        return result;
    }
};

int main() {
    int n, q; scanf("%d%d", &n, &q);
    
    vector<vector<pair<int, int>>>queries(n);
    
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i] = i + 1 - a[i];
        if(a[i] < 0)
            a[i] = inf;
    }
    
    for(int i = 0; i < q; i++) {
        int x, y; scanf("%d%d", &x, &y);
        queries[x].emplace_back(n - y - 1, i);
    }
    seg_tree_add_max t_max(a);
    seg_tree_add_sum t_ans(n);
    vector<int>answer(q);
    
    for(int i = n - 1; i >= 0; i--) {
        while(t_max.get_min(i, n - 1).first <= 0) {
            auto t = t_max.get_min(i, n - 1);
            
            if(t.first == 0) {
                t_ans.add(t.second, 1);
                t_max.add(t.second, n - 1, -1);
            }
            t_max.add(t.second, t.second, inf);
        }
        
        for(auto [j, ind] : queries[i]) {
            answer[ind] = t_ans.get_sum(i, j);
        }
    }
    
    for(int x : answer)
        printf("%d\n", x);
    
    return 0;
}
