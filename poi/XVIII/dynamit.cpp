#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int inf = 1 << 30;
const int MAX_N = 300'007;

vector<int>adj[MAX_N];
int depth[MAX_N], sorted_by_depth[MAX_N], parent[MAX_N];
bool dynamite[MAX_N];
int deepest_subtree_dynamite[MAX_N];
int closest_subtree_toggled[MAX_N];
int n, m, k;

void depth_dfs(int x, int p) {
    for(int y : adj[x]) {
        if(y != p) {
            parent[y] = x;
            depth[y] = depth[x] + 1;
            depth_dfs(y, x);
        }
    }
}

bool depth_cmp(int a, int b) {
    return depth[a] < depth[b];
}

int minimum_ignited_nodes() {
    
    int ignited_nodes = 0;
    for(int i = n - 1; i >= 0; i--) {
        int x = sorted_by_depth[i];
        
        
        deepest_subtree_dynamite[x] = -inf;
        closest_subtree_toggled[x] = inf;
        if(dynamite[x])
            deepest_subtree_dynamite[x] = 0;
        
        for(int y : adj[x]) {
            if(y == parent[x])
                continue;
            deepest_subtree_dynamite[x] = max(deepest_subtree_dynamite[x], deepest_subtree_dynamite[y] + 1);
            closest_subtree_toggled[x] = min(closest_subtree_toggled[x], closest_subtree_toggled[y] + 1);
        }
        
        if(deepest_subtree_dynamite[x] + closest_subtree_toggled[x] <= k) {
            deepest_subtree_dynamite[x] = -inf;
        }
        
        if(deepest_subtree_dynamite[x] == k) {
            ignited_nodes++;
            closest_subtree_toggled[x] = 0;
            deepest_subtree_dynamite[x] = -inf;
        }
        
    }
    
    if(deepest_subtree_dynamite[0] >= 0)
        ignited_nodes++;
    
    return ignited_nodes;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int d; cin >> d;
        dynamite[i] = d == 1;
    }
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    
    parent[0] = -1;
    depth_dfs(0, -1);
    
    iota(sorted_by_depth, sorted_by_depth + n, 0);
    sort(sorted_by_depth, sorted_by_depth + n, depth_cmp);
    
    int lo = 0, hi = n - 1;
    while(lo < hi) {
        k = (lo + hi) / 2;
        
        int ignited_nodes = minimum_ignited_nodes();
        
        if(ignited_nodes <= m) {
            hi = k;
        } else {
            lo = k + 1;
        }
        
    }
    
    cout << lo << '\n';
    
    return 0;
}
