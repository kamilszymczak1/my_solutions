#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, int p, vector<vector<int>>&adj, vector<int>&depth) {
    for(int y : adj[x]) {
        if(y != p) {
            depth[y] = depth[x] + 1;
            DFS(y, x, adj, depth);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, q; cin >> n >> q;
    vector<vector<int>>adj(n);
    vector<int>depth(n, 0);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    
    DFS(0, -1, adj, depth);
    
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        cout << ((depth[a - 1] + depth[b - 1]) % 2 == 0 ? "Town" : "Road") << '\n';
    }
    
    
    return 0;
}
