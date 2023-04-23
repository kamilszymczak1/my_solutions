#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 30;

int DFS(int x, int p, vector<vector<int>>&adj, vector<int>&h){ 
    int result = h[x];
    for(int y : adj[x]) {
        if(y == p)
            continue;
        result = max(result, DFS(y, x, adj, h));
    }
    return result;
}

bool Check(vector<int>&h, vector<int>&newH, vector<vector<int>>&adj) {
//     cout << "newH = ";
//     for(int x : newH)
//         cout << x << ' ';
//     cout << '\n';
    int n = h.size();
    for(int i = 0; i < n; i++) {
        int cnt = 0;
        if(newH[i] >= h[i])
            cnt++;
        for(int j : adj[i]) {
            if(DFS(j, i, adj, newH) >= h[i]) {
                cnt++;
            }
        }
        if(cnt < 2) {
            return false;
        }
    }
    return true;
}

long long Gen(int x, vector<int>&leaves, vector<int>&h, vector<int>&newH, vector<vector<int>>&adj, int maxH, int cost) {
    if(x == leaves.size())
        return Check(h, newH, adj) ? cost : inf;
    int node = leaves[x];
    long long result = inf;
    for(int i = h[node]; i <= maxH; i++) {
        newH[node] = i;
        result = min(result, Gen(x + 1, leaves, h, newH, adj, maxH, cost + i));
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>h(n), newH(n, 0);
    for(int &x : h)
        cin >> x;
    vector<vector<int>>adj(n);
    for(int i = 0; i < n - 1; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int maxH = *max_element(h.begin(), h.end());
    vector<int>leaves;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 1) {
            leaves.push_back(i);
        }
    }
    cout << Gen(0, leaves, h, newH, adj, maxH, 0) << '\n';
    
    return 0;
}
