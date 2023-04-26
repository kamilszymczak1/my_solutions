#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>>adj, newAdj;
vector<int>black, blackSubtree;
vector<bool>visited;

int DFS1(int x, int p) {
    blackSubtree[x] = black[x];
    for(int y : adj[x]) {
        if(y != p) {
            blackSubtree[x] += DFS1(y, x);
        }
    }
    return blackSubtree[x];
}

void DFS2(int x, int p, int blackAbove) {
    for(int y : adj[x]) {
        if(y != p) {
            if(blackAbove + blackSubtree[x] - blackSubtree[y] >= 2)
                newAdj[x].push_back(y);
            if(blackSubtree[y] >= 2)
                newAdj[y].push_back(x);
            DFS2(y, x, blackAbove + blackSubtree[x] - blackSubtree[y]);
        }
    }
}

void DFS3(int x) {
    visited[x] = true;
    for(int y : newAdj[x]) {
        if(!visited[y]) {
            DFS3(y);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    adj.resize(n); newAdj.resize(n); black.resize(n);
    for(auto &x : black)
        cin >> x;
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    blackSubtree.resize(n, 0);
    DFS1(0, -1);
    DFS2(0, -1, 0);
    visited.resize(n);
    for(int i = 0; i < n; i++) {
        for(int y : adj[i]) {
            if(black[y] == 1) {
                black[i] = 2;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(black[i] && !visited[i]) {
            DFS3(i);
        }
    }
    
    for(int i = 0; i < n; i++) {
        bool ok = black[i] || visited[i];
        cout << ok << ' ';
    }
    cout << '\n';
    
    return 0;
}
