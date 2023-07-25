#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
    
using namespace std;
    
void go(int x, vector<vector<int>>&adj, vector<int>&visited, vector<int>&color, vector<bool>&key) {
    visited[x] = 1;
    for(int y : adj[x]) {
        if(visited[y] == 0 && key[color[y]] == true) {
            go(y, adj, visited, color, key);
        }
    }
}
    
void recolor(int x, vector<vector<int>>&adj, vector<int>&visited, vector<int>&color, vector<bool>&key, vector<int>&pattern) {
    visited[x] = 1;
    color[x] = pattern[color[x]];
    for(int y : adj[x]) {
        if(visited[y] == 0 && key[color[y]] == true) {
            recolor(y, adj, visited, color, key, pattern);
        }
    }
}
    
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n);
    vector<pair<int, int>>c(n);
    for(auto &[x, y] : c)
        cin >> x >> y;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    
    auto cmp = [&](int a, int b) {
        return c[a] < c[b];
    };
    
    vector<int>order(n);
    for(int i = 0; i < n; i++)
        order[i] = i;
    sort(order.begin(), order.end(), cmp);
    vector<int>color(n, -1), visited(n, -1);
    color[0] = 0;
    color[1] = 1;
    color[2] = 2;
    color[3] = 3;
    for(int x : order) {
        
        if(color[x] != -1)
            continue;
        
        vector<int>nei(4, -1);
        
        for(int y : adj[x]) {
            if(c[y] > c[x])
                continue;
            if(c[y].first == c[x].first)
                nei[3] = y;
            if(c[y].second == c[x].second)
                nei[1] = y;
            if(c[y].first - c[y].second == c[x].first - c[x].second)
                nei[2] = y;
            if(c[y].first + c[y].second == c[x].first + c[x].second)
                nei[0] = y;
        }
        
        vector<bool>color_appear(4, false);
        for(int y : nei) {
            if(y != -1) {
                color_appear[color[y]] = true;
            }
        }
        
        bool color_found = false;
        for(int i = 0; i < 4; i++) {
            if(color_appear[i] == false) {
                color[x] = i;
                color_found = true;
                break;
            }
        }
        
        if(color_found)
            continue;
        
        vector<bool>key(4, false);
        key[color[nei[0]]] = true;
        key[color[nei[2]]] = true;
        
        for(int y : order) {
            if(x == y)
                break;
            visited[y] = 0;
        }
        
        go(nei[0], adj, visited, color, key);
        
        
        
        fill(key.begin(), key.end(), false);
        
        if(visited[nei[2]] == 1) {
            
            for(int y : order) {
                if(x == y)
                    break;
                visited[y] = 0;
            }
                
            vector<int>pattern(4, 0);
            pattern[color[nei[1]]] = color[nei[3]];
            pattern[color[nei[3]]] = color[nei[1]];
            key[color[nei[1]]] = key[color[nei[3]]] = true;
            color[x] = color[nei[1]];
            recolor(nei[1], adj, visited, color, key, pattern);
        } else {
            
            for(int y : order) {
                if(x == y)
                    break;
                visited[y] = 0;
            }
            
            vector<int>pattern(4, 0);
            pattern[color[nei[2]]] = color[nei[0]];
            pattern[color[nei[0]]] = color[nei[2]];
            key[color[nei[0]]] = key[color[nei[2]]] = true;
            color[x] = color[nei[0]];
            recolor(nei[0], adj, visited, color, key, pattern);
        }
    }
    
    for(int x : color) {
        cout << x + 1 << ' ';
    }
        
    cout << '\n';
    
    return 0;
}
