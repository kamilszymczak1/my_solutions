#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200'007;

vector<int>adj[MAX_N];
int lo[MAX_N], pre[MAX_N], post[MAX_N], pre_count = 0;
bool visited[MAX_N], articulation_point[MAX_N];
vector<pair<pair<int, int>, int>>children_range[MAX_N];
int subtree[MAX_N], independent_subtree[MAX_N];

const int inf = 1ll << 30;

void dfs(int x, int p) {
    pre[x] = pre_count++;
    lo[x] = pre[x];
    visited[x] = true;
    subtree[x] = 1;
    for(int y : adj[x]) {
        if(visited[y]) {
            if(y != p)
                lo[x] = min(lo[x], pre[y]);
        } else {
            dfs(y, x);
            subtree[x] += subtree[y];
            if(lo[y] >= pre[x]) {
                independent_subtree[x] += subtree[y];
                articulation_point[x] = true;
            }
            lo[x] = min(lo[x], lo[y]);
        }
    }
}

void dfs2(int x, int p) {
    visited[x] = true;
    pre[x] = pre_count++;
    if(articulation_point[x]) {
        for(int y : adj[x]) {
            if(!visited[y]) {
                int l = pre_count;
                dfs2(y, x);
                if(lo[y] >= pre[x])
                    children_range[x].emplace_back(make_pair(l, pre_count - 1), y);
            }
        }
    } else {
        for(int y : adj[x]) {
            if(!visited[y]) {
                dfs2(y, x);
            }
        }
    }
    
    post[x] = pre_count - 1;
}

void test_case() {
    
    int n, m; cin >> n >> m;
    
    pre_count = 0;
    fill(visited, visited + n, false);
    fill(articulation_point, articulation_point + n, false);
    fill(independent_subtree, independent_subtree + n, 0);
    for(int i = 0; i < n; i++) {
        adj[i].clear();
        children_range[i].clear();
    }
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    visited[0] = true;
    pre[0] = pre_count++;
    lo[0] = 0;
    int calls = 0;
    for(int x : adj[0]) {
        if(!visited[x]) {
            int l = pre_count;
            calls++;
            dfs(x, 0);
            children_range[0].emplace_back(make_pair(l, pre_count - 1), x);
        }
    }
    
    if(calls > 1) {
        articulation_point[0] = true;
    }
    
    pre_count = 0;
    fill(visited, visited + n, false);
    visited[0] = true;
    pre[0] = pre_count++;
    independent_subtree[0] = n - 1;
    for(int x : adj[0]) {
        if(!visited[x]) {
            dfs2(x, 0);
        }
    }
    
    int q; cin >> q;
    
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b; a--; b--;
        
        int output = n;
        
        for(int j = 0; j < 2; j++) {
            if(articulation_point[a]) {
                auto it = lower_bound(children_range[a].begin(), children_range[a].end(), make_pair(make_pair(pre[b], inf), inf));
                if(it == children_range[a].begin()) {
                    output -= independent_subtree[a];
                } else {
                    it--;
                    if(it -> first.first <= pre[b] && pre[b] <= it -> first.second) {
                        output -= n - subtree[it -> second] - 1;
                    } else {
                        output -= independent_subtree[a];
                    }
                }
            }
            swap(a, b);
        }
        
        
        
        cout << output << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
