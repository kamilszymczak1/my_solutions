#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const long long inf = 1ll << 30;

struct SegTree {
    struct Node {
        long long value, lazy;
        Node() : value(0), lazy(0) {}
    };
    vector<Node>nodes;
    int leafCount;
    SegTree(int n, long long fill) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        nodes.resize(leafCount * 2);
        for(int i = 0; i < leafCount * 2; i++)
            nodes[i].value = fill;
    }
    void Propagate(int v) {
        for(int i = 0; i < 2; i++) {
            nodes[v * 2 + i].value += nodes[v].lazy;
            nodes[v * 2 + i].lazy += nodes[v].lazy;
        }
        nodes[v].lazy = 0;
    }
    void AddRec(int a, int b, int lo, int hi, int v, long long value) {
        if(a == lo && b == hi) {
            nodes[v].value += value;
            nodes[v].lazy += value;
            return;
        }
        if(a >= b)
            return;
        Propagate(v);
        int mid = (lo + hi) / 2;
        AddRec(a, min(b, mid), lo, mid, v * 2, value);
        AddRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
        nodes[v].value = max(nodes[v * 2].value, nodes[v * 2 + 1].value);
    }
    void Add(int a, int b, long long value) {
        AddRec(a, b + 1, 0, leafCount, 1, value);
    }
    long long GetMaxRec(int a, int b, int lo, int hi, int v) {
        if(a == lo && b == hi)
            return nodes[v].value;
        if(a >= b)
            return -inf * 100;
        Propagate(v);
        int mid = (lo + hi) / 2;
        long long L = GetMaxRec(a, min(b, mid), lo, mid, v * 2);
        long long R = GetMaxRec(max(a, mid), b, mid, hi, v * 2 + 1);
        return max(L, R);
    }
    long long GetMax(int a, int b) {
        return GetMaxRec(a, b + 1, 0, leafCount, 1);
    }
};

void Scale(vector<long long>&v) {
    map<long long, vector<int>>pos;
    for(int i = 0; i < (int)v.size(); i++)
        pos[v[i]].push_back(i);
    int t = 0;
    for(auto [nothing, vec] : pos) {
        for(int x : vec)
            v[x] = t;
        t++;
    }
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>a(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        a[i] += a[i - 1];
    }
    Scale(a);
    vector<long long>bestWithSum(n + 1, -inf);
    SegTree T1(n + 1, -inf), T2(n + 1, -inf);
    
    bestWithSum[a[0]] = 0;
    T1.Add(a[0], a[0], inf);
    T2.Add(a[0], a[0], inf);

    vector<long long>dp(n + 1, -inf);
    dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        
        T1.Add(0, n, 1);
        T2.Add(0, n, -1);
        
        if(a[i] > 0)
            dp[i] = max(dp[i], T1.GetMax(0, a[i] - 1));
        if(a[i] < n)
            dp[i] = max(dp[i], T2.GetMax(a[i] + 1, n));
        
        dp[i] = max(dp[i], bestWithSum[a[i]]);
        
        long long toAdd = max(0ll, dp[i] - T1.GetMax(a[i], a[i]));
        T1.Add(a[i], a[i], toAdd);
        
        toAdd = max(0ll, dp[i] - T2.GetMax(a[i], a[i]));
        T2.Add(a[i], a[i], toAdd);
        bestWithSum[a[i]] = max(bestWithSum[a[i]], dp[i]);
    }
    printf("%lld\n", dp[n]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
