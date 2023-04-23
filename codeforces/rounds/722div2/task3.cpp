#include <iostream>
#include <vector>

using namespace std;

typedef long long int64;

void DFS(int x, int p, vector<vector<int>>&adj, vector<pair<int64, int64>>&bound, vector<pair<int64, int64>>&dp) {
    dp[x] = {0, 0};
    for(auto y : adj[x]) {
        if(y != p) {
            DFS(y, x, adj, bound, dp);
            int64 type1 = abs(bound[x].first - bound[y].first) + dp[y].first;
            int64 type2 = abs(bound[x].first - bound[y].second) + dp[y].second;
            dp[x].first += max(type1, type2);
            
            int64 type3 = abs(bound[x].second - bound[y].first) + dp[y].first;
            int64 type4 = abs(bound[x].second - bound[y].second) + dp[y].second;
            dp[x].second += max(type3, type4);
        }
    }
}

void TestCase() {
    int n; cin >> n;
    vector<vector<int>>adj(n, vector<int>());
    vector<pair<int64, int64>>bound(n);
    vector<pair<int64, int64>>dp(n);
    
    for(int i = 0; i < n; i++)
        cin >> bound[i].first >> bound[i].second;
    
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    
    DFS(0, -1, adj, bound, dp);
    
    cout << max(dp[0].first, dp[0].second) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
