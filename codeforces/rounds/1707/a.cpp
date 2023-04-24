#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

const int inf = 1 << 25;

struct SegTree {
    struct Node {
        int lazy;
        pair<int, int>hi;
        Node() : hi(make_pair(-inf, 0)), lazy(0) {}
    };
    vector<Node>nodes;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        nodes.resize(leafCount * 2);
        for(int i = 0; i < leafCount; i++)
            nodes[i + leafCount].hi = make_pair(-inf, i);
        for(int i = leafCount - 1; i >= 0; i--)
            nodes[i].hi = max(nodes[i * 2].hi, nodes[i * 2 + 1].hi);
    }
    
    void Push(int x) {
        for(int i = 0; i < 2; i++) {
            nodes[x * 2 + i].hi.first += nodes[x].lazy;
            nodes[x * 2 + i].lazy += nodes[x].lazy;
        }
        
        nodes[x].lazy = 0;
    }
    void Add(int a, int b, int value) {
        AddRec(a, b + 1, 0, leafCount, 1, value);
    }
    void AddRec(int a, int b, int lo, int hi, int v, int value) {
        if(a == lo && b == hi) {
            nodes[v].lazy += value;
            nodes[v].hi.first += value;
            return;
        }
        if(a >= b)
            return;
        Push(v);
        int mid = (lo + hi) / 2;
        AddRec(a, min(b, mid), lo, mid, v * 2, value);
        AddRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
        nodes[v].hi = max(nodes[v * 2].hi, nodes[v * 2 + 1].hi);
    }
    
    pair<int, int> GetMax(int a, int b) {
        return GetMaxRec(a, b + 1, 0, leafCount, 1);
    }
    
    pair<int, int> GetMaxRec(int a, int b, int lo, int hi, int v) {
        if(a == lo && b == hi)
            return nodes[v].hi;
        if(a >= b)
            return make_pair(-inf, 0);
        Push(v);
        int mid = (lo + hi) / 2;
        auto L = GetMaxRec(a, min(b, mid), lo, mid, v * 2);
        auto R = GetMaxRec(max(a, mid), b, mid, hi, v * 2 + 1);
        return max(L, R);
    }
};

void TestCase() {
    int n, q; scanf("%d%d", &n, &q);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    if(q >= n) {
        for(int i = 0; i < n; i++)
            putchar('1');
        putchar('\n');
        return;
    }
    
    vector<int>smaller;
    for(int i = 0; i < n; i++) {
        if(a[i] <= q) {
            smaller.push_back(i);
        }
    }
    
    if(smaller.empty()) {
        for(int i = 0; i < q; i++)
            putchar('1');
        for(int i = 0; i < n - q; i++)
            putchar('0');
        putchar('\n');
        return;
    }
    vector<bool>answer(n, false);
    SegTree T(n);
    for(int x : smaller) {
        answer[x] = true;
        T.Add(x, x, inf - q + a[x]);
    }
    
    int currentQ = q;
    int suffixMax = 0, suffixCount = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] <= q) {
            suffixMax = max(suffixMax, a[i]);
        } else {
            if(currentQ > suffixMax) {
                currentQ--;
                T.Add(i, n - 1, 1);
                answer[i] = true;
            } else {
                break;
            }
        }
    }
    
    
    for(int i = n - 1; i >= 0 && currentQ > 0; i--) {
        if(answer[i] == true)
            continue;
        T.Add(i, n - 1, 1);
        currentQ--;
        while(T.GetMax(0, n - 1).first > 0) {
            auto p = T.GetMax(0, n - 1);
            T.Add(p.second, p.second, -inf);
            T.Add(p.second, n - 1, 1);
            currentQ--;
        }
        
        if(currentQ >= 0)
            answer[i] = true;
    }
    for(int i = 0; i < n; i++)
        printf("%d", (int)answer[i]);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
