#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int a, b, w, id;
    Edge(int _a, int _b, int _w, int _id) : a(_a), b(_b), w(_w), id(_id) {}
};

bool cmp(Edge &a, Edge &b) {
    return a.w < b.w;
}

struct DSU {
    vector<int>f;
    DSU(int size) {
        f.resize(size);
        for(int i = 0; i < size; i++)
            f[i] = i;
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int a, int b) {
        f[Find(a)] = Find(b);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, m, q; cin >> n >> m >> q;
    vector<Edge>edges;
    for(int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        edges.emplace_back(a - 1, b - 1, w, -1);
    }
    for(int i = 0; i < q; i++) {
        int a, b, w; cin >> a >> b >> w;
        edges.emplace_back(a - 1, b - 1, w, i);
    }
    sort(edges.begin(), edges.end(), cmp);
    DSU d(n);
    vector<bool>ans(q, false);
    for(Edge &e : edges) {
        if(d.Find(e.a) != d.Find(e.b)) {
            if(e.id == -1) {
                d.Union(e.a, e.b);
            } else {
                ans[e.id] = true;
            }
        }
    }
    for(bool b : ans) {
        cout << (b ? "Yes" : "No") << '\n';
    }
    return 0;
}
