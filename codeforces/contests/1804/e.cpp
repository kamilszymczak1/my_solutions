#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

const int MAX_N = 20;

char parent[1 << MAX_N][MAX_N];
bitset<MAX_N>path[1 << MAX_N];
int n, m, nei_mask[MAX_N];
vector<pair<int, int>>edges;
vector<int>adj[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        edges.emplace_back(x - 1, y - 1);
        edges.emplace_back(y - 1, x - 1);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    for(int i = 0; i < n; i++) {
        nei_mask[i] |= 1 << i;
        for(int j : adj[i]) {
            nei_mask[i] |= 1 << j;
        }
    }
    
    for(int i = 0; i < n; i++) {
        path[1 << i][i] = true;
        parent[1 << i][i] = i;
    }
    
    for(int mask = 1; mask < (1 << n); mask++) {
        
        int z = 0;
        while(((1 << z) & mask) == 0)
            z++;
        
        for(auto [x, y] : edges) {
            if(((mask >> y) & 1) != 0)
                continue;
            if(path[mask][x]) {
                if(z < y) {
                    path[mask | (1 << y)][y] = true;
                    parent[mask | (1 << y)][y] = x;
                }
            }
        }
    }
    
    for(int mask = 1; mask < (1 << n); mask++) {
        int z = 0;
        while(((1 << z) & mask) == 0)
            z++;
        
        for(int j : adj[z]) {
            if(path[mask][j]) {
                path[mask][z] = true;
                parent[mask][z] = j;
            }
        }
    }
    
    for(int mask = 1; mask < (1 << n); mask++) {
        
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if((nei_mask[i] & mask) == 0) {
                ok = false;
                break;
            }
        }
        
        if(!ok)
            continue;
        
        int z = 0;
        while(((1 << z) & mask) == 0)
            z++;
        
        if(path[mask][z]) {
            cout << "YES\n" << flush;
            vector<int>answer(n);
            if(parent[mask][z] == z) {
                answer[z] = adj[z][0];
            } else {
                vector<int>path(1, z);
                int current_mask = mask, j = parent[mask][z];
                do {
                    path.push_back(j);
                    current_mask ^= 1 << j;
                    j = parent[current_mask ^ (1 << j)][j];
                } while(j != z);
                
                for(int j = 0; j < (int)path.size(); j++)
                    answer[path[j]] = path[(j + 1) % path.size()];
            }
            
            for(int i = 0; i < n; i++) {
                if(((mask >> i) & 1) == 0) {
                    for(int j : adj[i]) {
                        if((mask >> j) & 1) {
                            answer[i] = j;
                            break;
                        }
                    }
                }
            }
            
            for(int i = 0; i < n; i++)
                cout << answer[i] + 1 << ' ';
            cout << '\n';
            
            return 0;
        }
        
    }
    
    cout << "NO\n";
    
    return 0;
}
