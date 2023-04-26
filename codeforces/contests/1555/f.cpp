#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2);
    }
    void Add(int x, int value) {
        for(x += leafCount; x; x /= 2)
            values[x] += value;
    }
    int GetSum(int a, int b) {
        a += leafCount; b += leafCount;
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


struct DSU {
    vector<int>f;
    DSU(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int a, int b) {
        f[Find(a)] = Find(b);
    }
};

struct Edge {
    int a, b, w;
    Edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w) {}
};

void DFS(int x, vector<vector<pair<int, int>>>&adj, vector<bool>&visited, vector<bool>&pathXOR, vector<int>&preOrder, vector<int>&postOrder, int &time, vector<vector<int>>&jump, vector<int>&depth) {
    preOrder[x] = time++;
    visited[x] = true;
    for(auto [y, w] : adj[x]) {
        if(!visited[y]) {
            depth[y] = depth[x] + 1;
            jump[y].push_back(x);
            pathXOR[y] = pathXOR[x] ^ w;
            DFS(y, adj, visited, pathXOR, preOrder, postOrder, time, jump, depth);
        }
    }
    postOrder[x] = time++;
}

int LCA(int a, int b, vector<vector<int>>&jump, vector<int>&depth) {
    if(depth[a] < depth[b])
        swap(a, b);
    for(int i = jump[a].size() - 1; i >= 0; i--) {
        if(i < jump[a].size() && depth[jump[a][i]] >= depth[b])
            a = jump[a][i];
    }
    if(a == b)
        return a;
    for(int i = jump[a].size(); i >= 0; i--) {
        if(i < jump[a].size() && jump[a][i] != jump[b][i]) {
            a = jump[a][i];
            b = jump[b][i];
        }
    }
    return jump[a][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, q; cin >> n >> q;
    
    vector<Edge>edges;
    vector<bool>ans(q, false);
    vector<vector<pair<int, int>>>adj(n);
    vector<vector<int>>jump(n);
    DSU dsu(n);
    
    for(int i = 0; i < q; i++) {
        int a, b, w; cin >> a >> b >> w;
        if(dsu.Find(a - 1) != dsu.Find(b - 1)) {
            adj[a - 1].emplace_back(b - 1, w);
            adj[b - 1].emplace_back(a - 1, w);
            dsu.Union(a - 1, b - 1);
            ans[i] = true;
        }
        edges.emplace_back(a - 1, b - 1, w);
    }
    
    vector<bool>visited(n, false);
    vector<bool>pathXOR(n, 0);
    vector<int>preOrder(n), postOrder(n), depth(n);
    int time = 0;
    DFS(0, adj, visited, pathXOR, preOrder, postOrder, time, jump, depth);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            adj[0].emplace_back(i, 0);
            adj[i].emplace_back(0, 0);
            jump[i].push_back(0);
            depth[i] = 1;
            DFS(i, adj, visited, pathXOR, preOrder, postOrder, time, jump, depth);
        }
    }
    
    bool newJump;
    int currentBit = 0;
    do {
        newJump = false;
        for(int i = 0; i < n; i++) {
            if(jump[i].size() < currentBit + 1)
                continue;
            if(jump[jump[i][currentBit]].size() < currentBit + 1)
                continue;
            jump[i].push_back(jump[jump[i][currentBit]][currentBit]);
            newJump = true;
        }
        currentBit++;
    } while(newJump);
    
    SegTree T(2 * n);
    
    for(int i = 0; i < q; i++) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        if((pathXOR[a] ^ pathXOR[b] ^ w) == 0)
            continue;
        int lca = LCA(a, b, jump, depth);
        
        int usedEdges = T.GetSum(0, preOrder[a]) + T.GetSum(0, preOrder[b]) - 2 * T.GetSum(0, preOrder[lca]);
        if(usedEdges == 0) {
            ans[i] = true;
            for(int y : {a, b}) {
                while(y != lca) {
                    T.Add(preOrder[y], 1);
                    T.Add(postOrder[y], -1);
                    y = jump[y][0];
                }
            }
        }
    }
    
    for(int i = 0; i < q; i++) {
        cout << (ans[i] ? "YES" : "NO") << '\n';
    }
    
    return 0;
}
