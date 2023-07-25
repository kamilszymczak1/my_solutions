#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, vector<int>&parent, vector<vector<int>>&adj, vector<int>&depth) {
    for(int y : adj[x]) {
        if(y != parent[x]) {
            parent[y] = x;
            depth[y] = depth[x] + 1;
            DFS(y, parent, adj, depth);
        }
    }
}

long long score(long long n, long long redNodes, long long blueNodes) {
    return (n - redNodes - blueNodes) * (redNodes - blueNodes);
}

void TestCase() {
    int n, k; cin >> n >> k;
    vector<vector<int>>adj(n);
    vector<int>parent(n), depth(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    parent[0] = -1;
    DFS(0, parent, adj, depth);
    vector<pair<int, int>>nodesWithDepth;
    for(int i = 0; i < n; i++)
        nodesWithDepth.emplace_back(depth[i], i);
    sort(nodesWithDepth.begin(), nodesWithDepth.end());
    vector<bool>marked(n, false);
    vector<int>markedNodes;
    for(int i = n - 1; i >= 0; i--) {
        int cnt = 0;
        for(int j = nodesWithDepth[i].second; j != -1 && !marked[j]; j = parent[j]) {
            marked[j] = true;
            cnt++;
        }
        markedNodes.push_back(cnt);
    }
    sort(markedNodes.begin(), markedNodes.end());
    int takenNodes = 0;
    long long result = -(1ll << 60);
    for(int i = 1; i <= k; i++) {
        takenNodes += markedNodes[n - i];
        int blue = 0, red = i;
        for(int j = 19; j >= 0; j--) {
            if(blue + (1 << j) <= n - takenNodes) {
                if(score(n, red, blue + (1 << j)) < score(n, red, blue + (1 << j) - 1)) {
                    blue += (1 << j);
                }
            }
        }
        result = max(result, score(n, red, blue));
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t = 1;
    while(t--)
        TestCase();
    
    
    return 0;
}
