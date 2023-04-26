#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, vector<vector<pair<int, int>>>&adj, vector<int>&depth, vector<int>&parent) {
    for(auto [y, w] : adj[x]) {
        if(y != parent[x]) {
            parent[y] = x;
            depth[y] = depth[x] + 1;
            DFS(y, adj, depth, parent);
        }
    }
}

void DFSDist(int x, vector<vector<pair<int, int>>>&adj, vector<int>&dist, vector<int>&parent) {
    for(auto [y, w] : adj[x]) {
        if(dist[y] > dist[x] + w) {
            dist[y] = dist[x] + w;
            DFSDist(y, adj, dist, parent);
        }
    }
}



bool Check(vector<vector<pair<int, int>>>&adj, vector<int>&depth, vector<int>&parent, int x, int result) {
    int deepest = max_element(depth.begin(), depth.end()) - depth.begin();
    
    for(int i = 0; deepest != 0 && i < result - x; i++)
        deepest = parent[deepest];
    
    vector<int>dist = depth;
    dist[deepest] = min(dist[deepest], x);
    DFSDist(deepest, adj, dist, parent);
    
    return *max_element(dist.begin(), dist.end()) <= result;
}

void TestCase() {
    int n; cin >> n;
    vector<vector<pair<int, int>>>adj(n);
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].emplace_back(y - 1, 1);
        adj[y - 1].emplace_back(x - 1, 1);
    }
    vector<int>depth(n), parent(n);
    depth[0] = 0; parent[0] = -1;
    DFS(0, adj, depth, parent);
    
    
    for(int x = 1; x <= n; x++) {
        int result = 0;
        for(int i = 11; i >= 0; i--) {
            result += 1 << i;
            if(Check(adj, depth, parent, x, result))
                result -= 1 << i;
        }
        cout << result + 1 << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
