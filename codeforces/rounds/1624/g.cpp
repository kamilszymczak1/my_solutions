#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int a, b, w;
    Edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w) {}
};

struct DSU {
    vector<int>f;
    DSU(int x) {
        f.resize(x);
        for(int i = 0; i < x; i++)
            f[i] = i;
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int a, int b) {
        f[Find(a)] = Find(b);
    }
};

bool Check(vector<Edge>&edges, int mask, int n) {
    DSU d(n);
    int taken = 0;
    for(Edge e : edges) {
        if((e.w & mask) == e.w && d.Find(e.a) != d.Find(e.b)) {
            d.Union(e.a, e.b);
            taken++;
        }
    }
    return taken == n - 1;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<Edge>edges(m, Edge(-1, -1, -1));
    for(int i = 0; i < m; i++) {
        cin >> edges[i].a >> edges[i].b >> edges[i].w;
        edges[i].a--; edges[i].b--;
    }
    int result = (1 << 30) - 1;
    for(int i = 29; i >= 0; i--) {
        if(Check(edges, result ^ (1 << i), n))
            result ^= 1 << i;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
