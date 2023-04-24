#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int T = 700;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>>adj(n), heavyAdj(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    
    
    for(int i = 0; i < n; i++) {
        for(int x : adj[i]) {
            if(adj[x].size() >= T) {
                heavyAdj[i].push_back(x);
            }
        }
    }
    
    vector<bool>set(n, false);
    vector<int>nonSetAdj(n);
    for(int i = 0; i < n; i++) {
        if(adj[i].size() >= T) {
            nonSetAdj[i] = adj[i].size();
        }
    }
    
    int m; cin >> m;
    int result = 1;
    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        if(x > 0) { //add
            x--;
            for(int y : heavyAdj[x])
                nonSetAdj[y]--;
            if(adj[x].size() < T) {
                nonSetAdj[x] = 0;
                for(int y : adj[x])
                    nonSetAdj[x] += !set[y];
            }
            result += nonSetAdj[x] - 1;
            set[x] = true;
        } else { //remove
            x = - x - 1;
            for(int y : heavyAdj[x])
                nonSetAdj[y]++;
            if(adj[x].size() < T) {
                nonSetAdj[x] = 0;
                for(int y : adj[x])
                    nonSetAdj[x] += !set[y];
            }
            result -= nonSetAdj[x] - 1;
            set[x] = false;
        }
        cout << result << '\n';
    }
}
