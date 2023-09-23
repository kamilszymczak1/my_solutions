#include <iostream>
#include <vector>
#include <set>

using namespace std;

const long long mod = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    
    vector<set<int>>layers(2);
    layers[0].insert(0);
    for(int i = 1; i < n; i++)
        layers[1].insert(i);
    
    vector<int>touched_count(n, 0), touched_last_time(n, -1);
    for(int i = 1; i < (int)layers.size(); i++) {
        
        for(int x : layers[i - 1]) {
            for(int y : adj[x]) {
                if(touched_last_time[y] != i) {
                    touched_last_time[y] = i;
                    touched_count[y] = 0;
                }
                touched_count[y]++;
            }
        }
        
        vector<int>to_move;
        for(int x : layers[i]) {
            if(touched_count[x] == (int)layers[i - 1].size() && touched_last_time[x] == i) {
                to_move.push_back(x);
            }
        }
        
        if(to_move.size() != 0) {
            layers.emplace_back();
        }
        
        for(int x : to_move) {
            layers[i].erase(x);
            layers[i + 1].insert(x);
        }

    }
    
    vector<int>ways(n, 0);
    ways[0] = 1;
    for(int i = 1; i < (int)layers.size(); i++) {
        int sum = 0;
        for(int x : layers[i - 1]) {
            sum += ways[x];
            if(sum >= mod)
                sum -= mod;
        }
        for(int x : layers[i]) {
            ways[x] = sum;
            for(int y : adj[x]) {
                if(layers[i - 1].count(y)) {
                    ways[x] -= ways[y];
                    if(ways[x] < 0)
                        ways[x] += mod;
                }
            }
        }
    }
    
    bool empty_layer = false;
    for(int i = 0; i < (int)layers.size(); i++) {
        if(layers[i].count(n - 1))
            break;
        if(layers[i].empty()) {
            empty_layer = true;
        }
    }
    
    if(empty_layer) {
        cout << "-1\n";
    } else {
        cout << ways[n - 1] << '\n';
    }
    
    return 0;
}
