#include <iostream>
#include <vector>

using namespace std;

bool DFS(int x, vector<vector<pair<int, bool>>>&adj, vector<bool>&visited, vector<bool>&r) {
    visited[x] = true;
    for(auto [y, b] : adj[x]) {
        if(!visited[y]) {
            r[y] = r[x] ^ b;
            if(!DFS(y, adj, visited, r)) {
                return false;
            }
        } else if(r[y] != (r[x] ^ b)) {
            return false;
        }
    }
    return true;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, bool>>>adj(n);
    vector<pair<pair<int, int>, int>>edges;
    for(int i = 0; i < n + m - 1; i++) {
        int a, b, c; cin >> a >> b >> c;
        if(i < n - 1) {
            edges.emplace_back(make_pair(a - 1, b - 1), c);
        }
        if(c != -1) {
            adj[a - 1].emplace_back(b - 1, __builtin_popcount(c) & 1);
            adj[b - 1].emplace_back(a - 1, __builtin_popcount(c) & 1);
        }
    }
    vector<bool>r(n, 0), visited(n, false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            r[i] = 0;
            if(!DFS(i, adj, visited, r)) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
    for(auto [p, w] : edges) {
        cout << p.first + 1 << ' ' << p.second + 1 << ' ';
        cout << (w == -1 ? (r[p.first] ^ r[p.second]) : w) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    
    
    return 0;
}
