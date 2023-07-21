#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void dfs(int x, int p, vector<bool>&visited, vector<set<int>>&adj, vector<int>&comp, bool &cycle) {
    visited[x] = true;
    comp.push_back(x);
    for(int y : adj[x]) {
        if(visited[y] && y != p) {
            cycle = true;
        }
        if(!visited[y]) {
            dfs(y, x, visited, adj, comp, cycle);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    vector<set<int>>adj(n);
    vector<set<int>>undir_adj(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; x--; y--;
        if(adj[y].find(x) != adj[y].end()) {
            undir_adj[x].insert(y);
            undir_adj[y].insert(x);
        }
        adj[x].insert(y);
    }
    
    vector<bool>safe(n, false);
    
    for(int i = 0; i < n; i++) {
        for(int j : adj[i]) {
            if(undir_adj[i].find(j) == undir_adj[i].end()) {
                safe[j] = true;
            }
        }
    }
    
    vector<bool>visited(n, false);
    
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            vector<int>comp;
            bool cycle = false;
            dfs(i, -1, visited, undir_adj, comp, cycle);
            bool ok = false;
            for(int x : comp)
                if(safe[x])
                    ok = true;
                
            if(ok || cycle)
                for(int x : comp)
                    safe[x] = true;
        }
    }
    
    bool answer = true;
    for(int i = 0; i < n; i++)
        if(!safe[i])
            answer = false;
        
    cout << (answer ? "YES" : "NO") << '\n';
    
    return 0;
}
