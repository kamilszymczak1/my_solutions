#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PostOrderDFS(int x, vector<vector<int>>&adj, vector<bool>&visited, vector<int>&postorder) {
    visited[x] = true;
    for(int y : adj[x]) {
        if(!visited[y]) {
            PostOrderDFS(y, adj, visited, postorder);
        }
    }
    postorder.push_back(x);
}

void SCCDFS(int x, vector<vector<int>>&adj, vector<int>&sccID, int id) {
    sccID[x] = id; 
    for(int y : adj[x]) {
        if(sccID[y] == -1) {
            SCCDFS(y, adj, sccID, id);
        }
    }
}

void FindSCC(vector<int>&sccID, vector<vector<int>>&adj, vector<vector<int>>&revAdj, vector<vector<int>>&sccAdj) {
    int n = adj.size();
    vector<bool>visited(n, false);
    vector<int>postorder;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            PostOrderDFS(i, adj, visited, postorder);
        }
    }
    
    while(!postorder.empty()) {
        int x = postorder.back();
        if(sccID[x] == -1) {
            SCCDFS(x, revAdj, sccID, sccAdj.size());
            sccAdj.emplace_back();
        }
        postorder.pop_back();
    }
    
    for(int i = 0; i < n; i++) {
        for(int y : adj[i]) {
            if(sccID[y] != sccID[i]) {
                sccAdj[sccID[i]].push_back(sccID[y]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n), revAdj(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        revAdj[y - 1].push_back(x - 1);
    }
    
    vector<int>sccID(n, -1);
    vector<vector<int>>sccAdj;
    FindSCC(sccID, adj, revAdj, sccAdj);
    
    int n1 = sccAdj.size();
    vector<int>topoOrder, sccSize(n1);
    vector<bool>visited(n1, false);
    for(int i = 0; i < n; i++)
        sccSize[sccID[i]]++;
    for(int i = 0; i < n1; i++) {
        if(!visited[i]) {
            PostOrderDFS(i, sccAdj, visited, topoOrder);
        }
    }
    
    reverse(topoOrder.begin(), topoOrder.end());
    vector<int>ans(n1);
    while(!topoOrder.empty()) {
        int x = topoOrder.back();
        ans[x] += sccSize[x];
        for(int y : sccAdj[x])
            ans[x] += ans[y];
        topoOrder.pop_back();
    }
    
    for(int i = 0; i < n; i++)
        cout << ans[sccID[i]] - 1 << '\n';
    
    return 0;
}
