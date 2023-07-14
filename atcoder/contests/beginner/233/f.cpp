#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct DSU {
    vector<int>f;
    DSU(int x) {
        f.resize(x);
        for(int i = 0; i < x; i++)
            f[i] = i;
    }
    int find(int a) {
        return f[a] == a ? a : f[a] = find(f[a]);
    }
    void merge(int a, int b) {
        f[find(a)] = find(b);
    }
};

void FixDFS(int x, vector<vector<pair<int, int>>>&adj, vector<bool>&visited, vector<vector<pair<int, int>>>&newAdj) {
    visited[x] = true;
    for(auto [y, id] : adj[x]) {
        if(!visited[y]) {
            newAdj[x].emplace_back(y, id);
            newAdj[y].emplace_back(x, id);
            FixDFS(y, adj, visited, newAdj);
        }
    }
}

void FixAdj(vector<vector<pair<int, int>>>&adj) {
    int n = adj.size();
    vector<vector<pair<int, int>>>newAdj(n);
    vector<bool>visited(n);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            FixDFS(i, adj, visited, newAdj);
        }
    }
    swap(adj, newAdj);
}

void NodesDFS(int x, int p, vector<vector<pair<int, int>>>&adj, vector<int>&nodes) {
    nodes.push_back(x);
    for(auto [y, id] : adj[x]) {
        if(y != p) {
            NodesDFS(y, x, adj, nodes);
        }
    }
}

int DFSFind(int x, vector<pair<int, int>>&parent, vector<vector<pair<int, int>>>&adj, vector<int>&p, int target) {
    if(p[x] == target)
        return x;
    for(auto [y, id] : adj[x]) {
        if(y != parent[x].first) {
            parent[y] = make_pair(x, id);
            int t = DFSFind(y, parent, adj, p, target);
            if(t != -1)
                return t;
        }
    }
    
    return -1;
}

int main() {
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<pair<int ,int>>>adj(n);
    vector<int>p(n);
    DSU dsu(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    int m; cin >> m;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].emplace_back(b - 1, i);
        adj[b - 1].emplace_back(a - 1, i);
        dsu.merge(a - 1, b - 1);
    }
    
    for(int i = 0; i < n; i++) {
        if(dsu.find(i) != dsu.find(p[i])) {
            cout << "-1\n";
            return 0;
        }
    }
    
    FixAdj(adj);
    vector<int>deg(n), ans;
    for(int i = 0; i < n; i++)
        deg[i] = adj[i].size();
    for(int i = 0; i < n; i++) {
        if(p[i] == i)
            continue;
        vector<int>nodes;
        NodesDFS(i, -1, adj, nodes);
        vector<int>leaves;
        for(int x : nodes) {
            if(deg[x] == 1) {
                leaves.push_back(x);
            }
        }
        
        while(!leaves.empty()) {
            vector<int>newLeaves;
            for(int x : leaves) {
                vector<pair<int, int>>parent(n, make_pair(-2, -2));
                parent[x] = make_pair(-1, -1);
                int y = DFSFind(x, parent, adj, p, x);
                while(parent[y].first != -1) {
                    swap(p[y], p[parent[y].first]);
                    ans.push_back(parent[y].second + 1);
                    y = parent[y].first;
                }
                for(auto [t, id] : adj[x]) {
                    deg[t]--;
                    if(deg[t] == 1)
                        newLeaves.push_back(t);
                }
            }
            swap(leaves, newLeaves);
        }
    }
    
    cout << ans.size() << '\n';
    for(int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';

    
    return 0;
}
