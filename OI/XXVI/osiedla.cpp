#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void Direct(int x, vector<vector<pair<int, int>>>&undirected, vector<bool>&visited, vector<int>&direction) {
    visited[x] = true;
    for(auto [y, id] : undirected[x]) {
        if(direction[abs(id) - 1] == -1) {
            direction[abs(id) - 1] = id < 0;
        }
            
        if(!visited[y])
            Direct(y, undirected, visited, direction);
    }
}

void GetOrder(int x, vector<vector<int>>&adj, vector<bool>&visited, vector<int>&order) { 
    visited[x] = true;
    for(int y : adj[x]) {
        if(!visited[y]) {
            GetOrder(y, adj, visited, order);
        }
    }
    order.push_back(x);
}

void DFS(int x, vector<vector<int>>&adj, vector<bool>&visited) {
    visited[x] = true;
    for(int y : adj[x]) {
        if(!visited[y]) { 
            DFS(y, adj, visited);
        }
    }
}

int CountSCC(vector<vector<int>>&adj, vector<vector<int>>&adjT) {
    int n = adj.size();
    
    vector<int>order;
    vector<bool>visited(n, false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            GetOrder(i, adj, visited, order);
        }
    }
    fill(visited.begin(), visited.end(), false);
    int result = 0;
    while(!order.empty()) {
        if(!visited[order.back()]) {
            DFS(order.back(), adjT, visited);
            result++;
        }
        order.pop_back();
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>>undirected(n);
    
    
    for(int i = 1; i <= m; i++) { 
        int x, y; cin >> x >> y;
        undirected[x - 1].emplace_back(y - 1, +i);
        undirected[y - 1].emplace_back(x - 1, -i);
    }
    
    vector<bool>visited(m, false);
    vector<int>direction(m, -1); //0 -> normal, 1 -> reversed
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            Direct(i, undirected, visited, direction);
        }
        
    }
    
    vector<vector<int>>directed(n), directedT(n);
    
    for(int x = 0; x < n; x++) { 
        for(auto [y, id] : undirected[x]) {
            if(id < 0)
                continue;
            if(direction[id - 1] == 0) {
                directed[x].push_back(y);
                directedT[y].push_back(x);
            } else if(direction[id - 1] == 1) {
                directed[y].push_back(x);
                directedT[x].push_back(y);
            }
        }
    }
    
    cout << CountSCC(directed, directedT) << '\n';
    for(int i = 0; i < m; i++)
        cout << (direction[i] ? '>' : '<');
    cout << '\n';
    
    return 0;
}
