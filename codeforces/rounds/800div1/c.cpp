#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_N = 200'007;

const int inf = 1 << 30;

bool in_node[MAX_N], visited[MAX_N];
int n, m;
long long min_time[MAX_N];
vector<vector<pair<int, int>>adj[MAX_N];
vector<vector<pair<int, int>>special_adj[MAX_N];

void DFS1(int x) {
    visited[x] = true;
    if(x == n - 1) {
        visited[x]
        min_time[x] = 0;
        return;
    }
    
    min_time[x] = inf;
    
    long long default_cost = 0;
    
    vector<pair<long long, long long>>t;
    
    for(auto [y, w] : adj[x]) {
        
        default_cost += w;
        if(in_node[y]) {
            special_adj[x].emplace_back(y, w);
        } else {
            if(!visited[y])
                DFS1(y);
            t.emplace_back(min_time[y] + 1, w);
        }
        
    }
    
    sort(t.begin(), t.end());
    int s = t.size();
    for(int i = s - 1; i >= 0; i--) {
        default_cost -= t[i].second;
        min_time[x] = min(min_time[x], default_cost + t[i].first);
    }
    
    in_node[x] = false;
}

void DFS2(int x, int p) {
    
    visited[x] = true;
    
    if(x == n - 1) {
        min_time[x] = 0;
        return;
    }
    
    
    
}

int main() {
    scanf("%d%d", &n, &m);
    vector<pair<int, int>>edges;
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        edges.emplace_back(x - 1, y - 1);
    }
    sort(edges.begin(), edges.end());
    
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && edges[i] == edges[j])
            j++;
        adj[edges[i].first].emplace_back(edges[i].second, j - i);
        i = j - 1;
    }
    
    DFS1(0);
    fill(visited, visited + n, false);
    
    return 0;
}
