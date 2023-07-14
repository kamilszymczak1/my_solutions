#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void component_dfs(int x, int current_id, vector<vector<int>>&adj, vector<int>&comp_id) {
    comp_id[x] = current_id;
    for(int y : adj[x]) {
        if(comp_id[y] == -1) {
            component_dfs(y, current_id, adj, comp_id);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    vector<int>comp_id(n, -1);
    int current_id = 0;
    for(int i = 0; i < n; i++) {
        if(comp_id[i] == -1) {
            component_dfs(i, current_id++, adj, comp_id);
        }
    }
    
    vector<set<int>>component_adj(current_id);
    
    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        int x, y; cin >> x >> y; x--; y--;
        component_adj[comp_id[x]].insert(comp_id[y]);
        component_adj[comp_id[y]].insert(comp_id[x]);
    }
    
    int q; cin >> q;
    
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y; x--; y--;
        if(component_adj[comp_id[x]].find(comp_id[y]) == component_adj[comp_id[x]].end()) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    
    return 0;
}
