#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

const long long RANGE = 1 << 18;

struct SegTree {
    struct Node {
        int sum, lazy;
        Node() : sum(0), lazy(-1) {}
    };
    vector<Node>nodes;
    vector<pair<int, int>>myNodes;
    int leafCount;
    SegTree(vector<int>v) {
        int n = v.size();
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        nodes.resize(leafCount * 2);
        for(int i = 0; i < n; i++)
            nodes[i + leafCount].sum = v[i];
        for(int i = leafCount - 1; i > 0; i--)
            nodes[i].sum = nodes[i * 2].sum + nodes[i * 2 + 1].sum;
    }
    void Propagate(int x, int range) {
        if(nodes[x].lazy != -1) {
            for(int i = 0; i < 2; i++) {
                nodes[x * 2 + i].sum = nodes[x].lazy * range / 2;
                nodes[x * 2 + i].lazy = nodes[x].lazy;
            }
        }
        nodes[x].lazy = -1;
    }
    void Set(int a, int b, int value) {
        SetRec(a, b + 1, 0, leafCount, 1, value);
    }
    void SetRec(int a, int b, int lo, int hi, int v, int value) {
        if(a == lo && b == hi) {
            nodes[v].sum = value * (hi - lo);
            nodes[v].lazy = value;
            return;
        }
        if(a >= b)
            return;
        const int mid = (lo + hi) / 2;
        Propagate(v, hi - lo);
        SetRec(a, min(b, mid), lo, mid, v * 2, value);
        SetRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
        nodes[v].sum = nodes[v * 2].sum + nodes[v * 2 + 1].sum;
    }
    
    int FirstZeroRight(int x) {
        myNodes.clear();
        FindCrucialNodes(x, leafCount, 0, leafCount, 1);
        for(auto [v, range] : myNodes) {
            if(nodes[v].sum != range) {
                while(v < leafCount) {
                    Propagate(v, range);
                    v = v * 2;
                    if(nodes[v].sum == range / 2)
                        v++;
                    range /= 2;
                }
                return v - leafCount;
            }
        }
        return leafCount;
    }
    
    int FirstOneRight(int x) {
        myNodes.clear();
        FindCrucialNodes(x, leafCount, 0, leafCount, 1);
        for(auto [v, range] : myNodes) {
            if(nodes[v].sum > 0) {
                while(v < leafCount) {
                    Propagate(v, range);
                    v = v * 2;
                    if(nodes[v].sum == 0)
                        v++;
                    range /= 2;
                }
                return v - leafCount;
            }
        }
        return leafCount;
    }
    void FindCrucialNodes(int a, int b, int lo, int hi, int v) {
        if(a == lo && b == hi) {
            myNodes.emplace_back(v, hi - lo);
            return;
        }
        if(a >= b)
            return;
        const int mid = (lo + hi) / 2;
        Propagate(v, hi - lo);
        FindCrucialNodes(a, min(b, mid), lo, mid, v * 2);
        FindCrucialNodes(max(a, mid), b, mid, hi, v * 2 + 1);
    }
    
    int GetHighestOne() {
        int v = 1, range = leafCount;
        while(v < leafCount) {
            Propagate(v, range);
            if(nodes[v * 2 + 1].sum > 0) {
                v = v * 2 + 1;
            } else {
                v = v * 2 + 0;
            }
            range /= 2;
        }
        return v - leafCount;
    }
};

void TestCase() {
    int n, q; scanf("%d%d", &n, &q);
    vector<int>cnt(RANGE), a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
        cnt[a[i]]++;
    }
    for(int i = 0; i < RANGE - 1; i++) {
        cnt[i + 1] += cnt[i] / 2;
        cnt[i] %= 2;
    }
    SegTree T(cnt);
    for(int i = 0; i < q; i++) {
        int k, l; scanf("%d%d", &k, &l); k--; l--;
        
        int t;
        t = T.FirstOneRight(a[k]);
        T.Set(t, t, 0);
        if(t != a[k])
            T.Set(a[k], t - 1, 1);
        
        a[k] = l;
        t = T.FirstZeroRight(l);
        T.Set(t, t, 1);
        if(t != a[k])
            T.Set(a[k], t - 1, 0);
        
        printf("%d\n", T.GetHighestOne() + 1);
        
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
