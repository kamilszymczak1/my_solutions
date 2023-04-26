#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200'007;

pair<int, int>dp[MAX_N][2];
vector<pair<int, int>>children[MAX_N][2];
vector<int>adj[MAX_N];
int w[MAX_N], n;

pair<int, int>operator+ (const pair<int, int>p1, const pair<int, int>p2) {
    return make_pair(p1.first + p2.first, p1.second + p2.second);
}

bool Better(pair<int, int>a, pair<int, int>b) {
    if(a.first == b.first)
        return a.second <= b.second;
    return a.first > b.first;
}

void DFS(int x, int p) {
    dp[x][0] = make_pair(0, 1);
    dp[x][1] = make_pair(1, adj[x].size());
    for(int y : adj[x]) {
        if(y == p)
            continue;
        DFS(y, x);
        children[x][1].emplace_back(y, 0);
        dp[x][1] = dp[x][1] + dp[y][0];
        if(Better(dp[y][0], dp[y][1])) {
            children[x][0].emplace_back(y, 0);
            dp[x][0] = dp[x][0] + dp[y][0];
        } else {
            children[x][0].emplace_back(y, 1);
            dp[x][0] = dp[x][0] + dp[y][1];
        }
    }
}

void Colour(int x, int t) {
    w[x] = t == 0 ? 1 : adj[x].size();
    for(auto [y, s] : children[x][t])
        Colour(y, s);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    if(n == 2) {
        cout << "2 2\n1 1\n";
        return 0;
    }
    for(int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    DFS(0, -1);
    int ans = 0, sum = 0;
    if(Better(dp[0][1], dp[0][0])) {
        Colour(0, 1);
        ans = dp[0][1].first;
        sum = dp[0][1].second;
    } else {
        Colour(0, 0);
        ans = dp[0][0].first;
        sum = dp[0][0].second;
    }
    
    cout << ans << ' ' << sum << '\n';
    for(int i = 0; i < n; i++)
        cout << w[i] << ' ';
    cout << '\n';
    
    return 0;
}
