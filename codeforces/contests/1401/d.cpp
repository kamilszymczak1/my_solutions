#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long mod = 1000000007;

void DFS(int x, int p, vector<vector<int>>&adj, vector<int>&subtree) {
    subtree[x] = 1;
    for(int y : adj[x]) {
        if(y != p) {
            DFS(y, x, adj, subtree);
            subtree[x] += subtree[y];
        }
    }
}

void TestCase() {
    int n; cin >> n;
    vector<vector<int>>adj(n);
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int m; cin >> m;
    vector<int>p(m);
    for(auto &x : p)
        cin >> x;
    while(p.size() < n - 1)
        p.push_back(1);
    sort(p.begin(), p.end());
    while(p.size() > n - 1) {
        int s = p.size();
        p[s - 2] = (1ll * p[s - 2] * p[s - 1]) % mod;
        p.pop_back();
    }
    
    vector<int>subtree(n);
    DFS(0, -1, adj, subtree);
    vector<long long>edgeWeight;
    for(int i = 1; i < n; i++)
        edgeWeight.push_back(1ll * subtree[i] * (n - subtree[i]));
    sort(edgeWeight.begin(), edgeWeight.end());
    int result = 0;
    for(int i = 0; i < n - 1; i++) {
        edgeWeight[i] %= mod;
        result = (result + edgeWeight[i] * p[i]) % mod;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
