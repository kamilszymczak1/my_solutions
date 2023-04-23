#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 62;

const int MAX_N = 200007;

void DFS1(int x, int p, vector<vector<int>>&adj, vector<int>&h, vector<int>&maxH) {
    maxH[x] = h[x];
    for(int y : adj[x]) {
        if(y == p)
            continue;
        DFS1(y, x, adj, h, maxH);
        maxH[x] = max(maxH[x], maxH[y]);
    }
}

long long DFS2(int x, int p, vector<vector<int>>&adj, vector<int>&h, vector<int>&maxH, int required, int highestAbove) {
    vector<pair<int, int>>sons;
    for(int y : adj[x]) {
        if(y == p)
            continue;
        sons.emplace_back(maxH[y], y);
    }
    sort(sons.begin(), sons.end(), greater<pair<int, int>>());
    if(sons.size() == 0)
        return max(required, h[x]);
    if(sons.size() == 1)
        return DFS2(sons[0].second, x, adj, h, maxH, max(required, h[x]), highestAbove);
    long long result = 0;
    int newHighestAbove = max(max(h[x], highestAbove), max(sons[0].first, required));
    if(h[x] <= sons[1].first || h[x] <= highestAbove) {
        result += DFS2(sons[0].second, x, adj, h, maxH, max(required, h[x]), max(highestAbove, sons[1].first));
        for(int i = 1; i < (int)sons.size(); i++)
            result += DFS2(sons[i].second, x, adj, h, maxH, 0, newHighestAbove);
    } else {
        result += DFS2(sons[0].second, x, adj, h, maxH, max(required, h[x]), max(highestAbove, max(h[x], sons[1].first)));
        result += DFS2(sons[1].second, x, adj, h, maxH, h[x], newHighestAbove);
        for(int i = 2; i < (int)sons.size(); i++)
            result += DFS2(sons[i].second, x, adj, h, maxH, 0, newHighestAbove);
    }
    return result;
}

void TestCase() {
    int n; cin >> n;
    vector<vector<int>>adj(n);
    vector<int>h(n), maxH(n);
    for(auto &x : h)
        cin >> x;
    if(n == 2) {
        cout << max(h[0], h[1]) * 2 << '\n';
        return;
    }
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int root = max_element(h.begin(), h.end()) - h.begin();
    DFS1(root, -1, adj, h, maxH);
    if(adj[root].size() == 1) {
        cout << DFS2(root, -1, adj, h, maxH, h[root], h[root]) + h[root] << '\n';
    } else {
        cout << DFS2(root, -1, adj, h, maxH, 0, 0) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    
    return 0;
}
