#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool TestCase() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>>adj(2 * n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        while(x) {
            if(x <= n) {
                adj[i].push_back(x - 1 + n);
                adj[x - 1 + n].push_back(i);
            }
            x /= 2;
        }
    }
    vector<int>matching(2 * n, -1);
    for(int i = 0; i < n; i++) {
        vector<int>parent(n * 2, -2);
        parent[i] = -1;
        queue<int>q;
        bool found = false;
        for(q.push(i); !q.empty(); q.pop()) {
            int x = q.front();
            if(x >= n) {
                if(matching[x] == -1) {
                    while(parent[x] != -1) {
                        if(x >= n) {
                            matching[x] = parent[x];
                            matching[parent[x]] = x;
                        }
                        x = parent[x];
                    }
                    found = true;
                    break;
                } else if(parent[matching[x]] == -1) {
                    parent[matching[x]] = x;
                    q.push(matching[x]);
                }
            } else {
                for(int y : adj[x]) {
                    if(parent[y] == -2) {
                        parent[y] = x;
                        q.push(y);
                    }
                }
            }
        }
        if(!found)
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        if(TestCase()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        
        return 0;
}
