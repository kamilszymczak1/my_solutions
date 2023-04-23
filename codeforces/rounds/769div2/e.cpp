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

void DFSDist(int x, vector<vector<pair<int, int>>>&adj, vector<int>&dist) {
    for(auto [y, w] : adj[x]) {
        if(dist[y] > dist[x] + w) {
            dist[y] = dist[x] + w;
            DFSDist(y, adj, dist);
        }
    }
}



bool Check(int x, int result, vector<int>&furthestNodeAtLevel, int deepestDepth) { // can result be achieved
   // cout << "Check at " << x << ' ' << result << '\n';
    if(result + 1 >= furthestNodeAtLevel.size())
        return true;
    if(deepestDepth <= result)
        return true;
    if(result < x)
        return false;
    int furthest = furthestNodeAtLevel[result + 1];
    return furthest + x - (result - x) <= result;
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
    
    int deepest = max_element(depth.begin(), depth.end()) - depth.begin();
    
    vector<int>dist(n, 1 << 30);
    dist[deepest] = 0;
    DFSDist(deepest, adj, dist);
    
    vector<int>furthestNodeAtLevel(n, 0);
    
    for(int i = 0; i < n; i++)
        furthestNodeAtLevel[depth[i]] = max(furthestNodeAtLevel[depth[i]], dist[i]);
    
    for(int i = n - 2; i >= 0; i--)
        furthestNodeAtLevel[i] = max(furthestNodeAtLevel[i], furthestNodeAtLevel[i + 1]);
    
    for(int x = 1; x <= n; x++) {
        int result = 0;
        for(int i = 19; i >= 0; i--) {
            result += 1 << i;
            if(Check(x, result, furthestNodeAtLevel, depth[deepest]))
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
