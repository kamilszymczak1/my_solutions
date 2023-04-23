#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void TopoDFS(int x, vector<set<int>>&adj, vector<bool>&visited, vector<int>&topoOrder) {
    visited[x] = true;
    for(int y : adj[x]) {
        if(!visited[y]) {
            TopoDFS(y, adj, visited, topoOrder);
        }
    }
    topoOrder.push_back(x);
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<set<int>>out(n), in(n);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        out[x - 1].insert(y - 1);
        in[y - 1].insert(x - 1);
    }
    vector<bool>inRemoved(n, false), outRemoved(n, false);
    for(int i = 0; i < n; i++) {
        if(out[i].size() == 1 && outRemoved[i] == false) {
            int x = *out[i].begin();
            out[i].erase(out[i].begin());
            in[x].erase(in[x].find(i));
            outRemoved[i] = true;
            inRemoved[x] = true;
        }
        if(in[i].size() == 1 && inRemoved[i] == false) {
            int x = *in[i].begin();
            in[i].erase(in[i].begin());
            out[x].erase(out[x].find(i));
            outRemoved[x] = true;
            inRemoved[i] = true;
        }
    }
    
    vector<int>topoOrder;
    vector<bool>visited(n);
    for(int i = 0; i < n; i++) {
        if(visited[i] == false) {
            TopoDFS(i, out, visited, topoOrder);
        }
    }
    reverse(topoOrder.begin(), topoOrder.end());
    
    vector<int>ans(n, 1);
    for(int x : topoOrder) {
        for(int y : out[x]) {
            ans[y] = max(ans[y], ans[x] + 1);
        }
    }
    
    printf("%d\n", *max_element(ans.begin(), ans.end()));
    
    return 0;
}
