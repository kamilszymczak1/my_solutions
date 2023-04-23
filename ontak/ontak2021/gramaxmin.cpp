#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int Solve(vector<vector<int>>&adj, vector<int>&etiquette) {
    int n = adj.size();
    if(etiquette[0] == 2)
        return 2;
    vector<vector<int>>adjRev(n);
    vector<int>inDegRev(n, 0), inDegCurrent(n, 0), outDeg(n, 0);
    vector<bool>visited(n, false);
    for(int i = 0; i < n; i++) {
        for(int j : adj[i]) {
            if(etiquette[i] != etiquette[j]) {
                outDeg[i]++;
                adjRev[j].push_back(i);
                inDegRev[i]++;
            }
        }
    }
    queue<int>q;
    for(int i = 0; i < n; i++) {
        if(etiquette[i] == 2 && outDeg[i] == 0) {
            q.push(i);
            visited[i] = true;
        }
    }
    
    for(; !q.empty(); q.pop()) {
        int x = q.front();
        if(etiquette[x] == 2) {
            for(int y : adjRev[x]) {
                if(!visited[y]) {
                    q.push(y);
                    visited[y] = true;
                }
            }
        } else {
            for(int y : adjRev[x]) {
                inDegCurrent[y]++;
                if(inDegCurrent[y] == inDegRev[y] && !visited[y]) { 
                    q.push(y);
                    visited[y] = true;
                }
            }
        }
        
    }
    return visited[0] ? 2 : 1;
}


//is first player capable of scoring at least bound points
bool Check(int bound, vector<vector<int>>&adj, vector<int>&etiquette) {
    int n = adj.size();
    vector<int>newEtiquette(n);
    for(int i = 0; i < n; i++)
        newEtiquette[i] = etiquette[i] >= bound ? 2 : 1;
    return Solve(adj, newEtiquette) == 2;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, m; cin >> n >> m;
    vector<int>etiquette(n);
    for(int &x : etiquette)
        cin >> x;
    
    vector<vector<int>>adj(n);
    
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    
    int beg = 1, end = 1e9;
    
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if(Check(mid, adj, etiquette)) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    
    cout << beg - 1 << '\n';
    
    
    return 0;
}

/*
4 4
1 10 4 5
1 2
2 3
2 4
3 1
*/
