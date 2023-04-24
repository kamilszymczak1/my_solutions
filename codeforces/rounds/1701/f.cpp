#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

struct SegmentTree {
    struct Node {
        long long sum, lazy;
        int range;
        Node() : sum(0), lazy(0), range(0) {}
    };
    vector<Node>nodes;
    int leaf_count;
    SegmentTree(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        nodes.resize(leaf_count * 2);
    }
    
    void push(int v) {
        for(int i = 0; i < 2; i++) {
            nodes[v * 2 + i].sum += nodes[v * 2 + i].range * nodes[v].lazy;
            nodes[v * 2 + i].lazy += nodes[v].lazy;
        }
        nodes[v].lazy = 0;
    }
    
    void push_path(int lo, int hi, int v, int x) {
        if(hi - lo > 1) {
            push(v);
            int mid = (lo + hi) / 2;
            if(x < mid) {
                push_path(lo, mid, v * 2, x);
            } else {
                push_path(mid, hi, v * 2 + 1, x);
            }
        }
    }
    
    void add(int a, int b, long long value) {
        add(a, b + 1, 0, leaf_count, 1, value);
    }
    void add(int a, int b, int lo, int hi, int v, long long value) {
        if(a == lo && b == hi) {
            nodes[v].lazy += value;
            nodes[v].sum += nodes[v].range * value;
            return;
        }
        if(a >= b)
            return;
        push(v);
        int mid = (lo + hi) / 2;
        add(a, min(b, mid), lo, mid, v * 2, value);
        add(max(a, mid), b, mid, hi, v * 2 + 1, value);
        nodes[v].sum = nodes[v * 2].sum + nodes[v * 2 + 1].sum;
    }
    
    long long sum(int a, int b) {
        return sum(a, b + 1, 0, leaf_count, 1);
    }
    long long sum(int a, int b, int lo, int hi, int v) {
        if(a == lo && b == hi)
            return nodes[v].sum;
        if(a >= b)
            return 0;
        push(v);
        int mid = (lo + hi) / 2;
        long long L = sum(a, min(b, mid), lo, mid, v * 2);
        long long R = sum(max(a, mid), b, mid, hi, v * 2 + 1);
        return L + R;
    }
    
    void activate(int x, long long new_sum) {
        assert(nodes[x + leaf_count].range == 0);
        push_path(0, leaf_count, 1, x);
        for(x += leaf_count; x; x /= 2) {
            nodes[x].sum += new_sum;
            nodes[x].range++;
        }
        
    }
    
    void deactivate(int x) {
        assert(nodes[x + leaf_count].range == 1);
        push_path(0, leaf_count, 1, x);
        long long my_sum = nodes[x + leaf_count].sum;
        for(x += leaf_count; x; x /= 2) {
            nodes[x].sum -= my_sum;
            nodes[x].range--;
        }
    }
    
    int range_sum(int a, int b) {
        a += leaf_count;  b += leaf_count;
        int result = nodes[a].range;
        if(a != b)
            result += nodes[b].range;
        for(; a / 2 != b / 2; a /= 2, b /= 2) {
            if(a % 2 == 0)
                result += nodes[a + 1].range;
            if(b % 2 == 1)
                result += nodes[b - 1].range;
        }
        return result;
    }
};

const int RANGE = 200'007;

int main() {
    int n, d; scanf("%d%d", &n, &d);
    SegmentTree t(RANGE);
    vector<bool>active(RANGE);
    long long answer = 0;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        if(active[a]) {
            answer -= t.sum(max(0, a - d), a - 1);
            t.add(max(0, a - d), a - 1, -1);
            long long to_right = t.range_sum(a + 1, min(RANGE, a + d));
            answer -= to_right * (to_right - 1) / 2;
            t.deactivate(a);
        } else {
            t.add(max(0, a - d), a - 1, 1);
            answer += t.sum(max(0, a - d), a - 1);
            long long to_right = t.range_sum(a + 1, min(RANGE - 1, a + d));
            answer += to_right * (to_right - 1) / 2;
            t.activate(a, to_right - 1);
        }
        printf("%lld\n", answer);
        active[a] = !active[a];
    }
    
    return 0;
}
