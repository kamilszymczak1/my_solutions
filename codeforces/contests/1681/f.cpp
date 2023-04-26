#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>
#include <cstring>
#include <stack>

using namespace std;

void DFS(int x, int p, int lastE, vector<vector<pair<int, int>>>&adj, vector<int>&up, vector<int>&subtree, vector<stack<int>>&last, vector<vector<int>>&rootChildren) {
    if(last[lastE].size() > 0)
        up[x] = last[lastE].top();
    else
        rootChildren[lastE].push_back(x);
    last[lastE].push(x);
    for(auto [y, e] : adj[x]) {
        if(y == p)
            continue;
        DFS(y, x, e, adj, up, subtree, last, rootChildren);
        subtree[x] += subtree[y];
    }
    last[lastE].pop();
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<vector<pair<int, int>>>adj(n);
    for(int i = 1; i < n; i++) {
        int x, y, v; scanf("%d%d%d", &x, &y, &v);
        adj[x - 1].emplace_back(y - 1, v - 1);
        adj[y - 1].emplace_back(x - 1, v - 1);
    }
    
    vector<stack<int>>last(n);
    vector<int>up(n, -1), subtree(n, 1);
    vector<vector<int>>rootChildren(n);
    for(auto [y, e] : adj[0]) {
        DFS(y, 0, e, adj, up, subtree, last, rootChildren);
        subtree[0] += subtree[y];
    }
    
    vector<vector<int>>children(n);
    vector<int>colorSubtree(n, 0);
    
    for(int i = 0; i < n; i++)
        colorSubtree[i] = subtree[i];
    for(int i = 0; i < n; i++) {
        if(up[i] != -1) {
            children[up[i]].push_back(i);
        } else {
            children[0].push_back(i);
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int x : children[i]) {
            colorSubtree[i] -= subtree[x];
        }
    }
    
    long long result = 0;
    
    for(int i = 1; i < n; i++) {
        for(int x : children[i]) {
            result += 1ll * colorSubtree[x] * colorSubtree[i];
        }
    }
    
    for(int rootColor = 0; rootColor < n; rootColor++) {
        int rootColorSubtree = subtree[0];
        for(int x : rootChildren[rootColor])
            rootColorSubtree -= subtree[x];
        for(int x : rootChildren[rootColor])
            result += 1ll * rootColorSubtree * colorSubtree[x];
    }
    
    printf("%lld\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
