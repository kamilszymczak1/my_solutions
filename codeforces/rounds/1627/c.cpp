#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, int p, vector<vector<pair<int, int>>>&adj, vector<int>&result, int n) {
    for(auto [y, id] : adj[x]) {
        if(y != p) {
            result[id] = n;
            DFS(y, x, adj, result, n == 11 ? 2 : 11);
            if(n == 11) {
                n = 2;
            } else {
                n = 11;
            }
        }
    }
}

void TestCase() {
    int n; cin >> n;
    vector<vector<pair<int, int>>>adj(n);
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].emplace_back(y - 1, i);
        adj[y - 1].emplace_back(x - 1, i);
    }
    int maxDeg = 0;
    for(int i = 0; i < n; i++)
        maxDeg = max(maxDeg, (int)adj[i].size());
    if(maxDeg > 2) {
        cout << "-1\n";
        return;
    }
    vector<int>ans(n - 1);
    DFS(0, -1, adj, ans, 2);
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
