#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>
#warning CHECK MULTI TEST CASES!

using namespace std;

int DFS(int x, vector<vector<int>>&adj, vector<int>&visited, vector<int>&topoOrder) {
    visited[x] = 1;
    for(int y : adj[x]) {
        if(visited[y] == 1)
            return 1;
        if(visited[y] == 2)
            continue;
        if(DFS(y, adj, visited, topoOrder) == 1)
            return 1;
    }
    visited[x] = 2;
    topoOrder.push_back(x);
    return 0;
}

long long LongestPath(vector<vector<int>>&adj) {
    int n = adj.size();
    vector<int>topoOrder, visited(n, 0);
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            if(DFS(i, adj, visited, topoOrder) == 1) {
                return 1ll << 61; //there is a cycle
            }
        }
    }
    reverse(topoOrder.begin(), topoOrder.end());
    vector<int>ans(n, 1);
    for(int x : topoOrder)
        for(int y : adj[x]) {
            ans[y] = max(ans[y], ans[x] + 1);
        }
    return *max_element(ans.begin(), ans.end());
}

bool Check(vector<vector<int>>&adj, vector<int>&a, long long k, int ans) {
    int n = adj.size();
    vector<int>id(n, -1);
    int lastId = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] <= ans)
            id[i] = ++lastId;
    }
    if(lastId == -1)
        return false;
    vector<vector<int>>newAdj(lastId + 1);
    for(int i = 0; i < n; i++) {
        if(id[i] == -1)
            continue;
        for(int y : adj[i]) {
            if(id[y] == -1)
                continue;
            newAdj[id[i]].push_back(id[y]);
        }
    }
    return LongestPath(newAdj) >= k;
}

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    long long k; scanf("%lld", &k);
    vector<vector<int>>adj(n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
    }
    
    int ans = (1 << 30) - 1;
    for(int bit = 29; bit >= 0; bit--) {
        ans -= 1 << bit;
        if(Check(adj, a, k, ans) == false)
            ans += 1 << bit;
    }
    if(Check(adj, a, k, ans) == false) {
        printf("-1\n");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
