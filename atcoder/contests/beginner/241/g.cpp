#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int Extend(vector<vector<int>>&cap, vector<vector<int>>&flow, vector<vector<int>>&adj) {
    int n = cap.size();
    vector<int>p(n, -2), maxFlow(n, 0);
    queue<int>q;
    q.push(0);
    p[0] = -1;
    maxFlow[0] = 1 << 30;
    while(!q.empty()) {
        int x = q.front();
        for(int y : adj[x]) {
            if(cap[x][y] > flow[x][y] && p[y] == -2) {
                maxFlow[y] = min(maxFlow[x], cap[x][y] - flow[x][y]);
                p[y] = x;
                while(y == n - 1 && !q.empty())
                    q.pop();
                q.push(y);
            }
        }
        q.pop();
    }
    if(maxFlow[n - 1] != 0) {
        int x = n - 1;
        while(p[x] != -1) {
            flow[p[x]][x] += maxFlow[n - 1];
            flow[x][p[x]] -= maxFlow[n - 1];
            x = p[x];
        }
    }
    return maxFlow[n - 1];
}

int MaxFlow(vector<vector<int>>&cap, vector<vector<int>>&adj) {
    int n = cap.size(), result = 0, x;
    vector<vector<int>>flow(n, vector<int>(n, 0));
    do {
        x = Extend(cap, flow, adj);
        result += x;
    } while(x != 0);
    return result;
}

bool Check(int x, vector<vector<bool>>played, vector<int>won, int matchesToPlay) {
    int n = won.size();
    for(int i = 0; i < n; i++) {
        if(i != x && !played[i][x]) {
            played[i][x] = played[x][i] = true;
            won[x]++;
            matchesToPlay--;
        }
    }
    if(won[x] < n / 2)
        return false;
    
    int nodes = 2 + n + matchesToPlay; //source, sink, players, game
    vector<vector<int>>adj(nodes);
    vector<vector<int>>flow(nodes, vector<int>(nodes, 0)), cap(nodes, vector<int>(nodes, 0));
    for(int i = 1; i <= n; i++) {
        if(i == x + 1)
            continue;
        if(won[i - 1] >= won[x]) {
            return false;
        }
        adj[0].push_back(i);
        adj[i].push_back(0);
        cap[0][i] = won[x] - won[i - 1] - 1;
    }
        
    int ind = n + 1;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(!played[i][j]) {
                adj[i + 1].push_back(ind);
                adj[j + 1].push_back(ind);
                adj[ind].push_back(i + 1);
                adj[ind].push_back(j + 1);
                adj[ind].push_back(nodes - 1);
                adj[nodes - 1].push_back(ind);
                cap[i + 1][ind] = 1;
                cap[j + 1][ind] = 1;
                cap[ind][nodes - 1] = 1;
                ind++;
                played[i][j] = played[j][i] = true;
            }
        }
    }
    
    return MaxFlow(cap, adj) == matchesToPlay;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<bool>>played(n, vector<bool>(n, false));
    vector<int>won(n, 0);
    for(int i = 0; i < n; i++)
        played[i][i] = true;
    for(int i = 0; i < m; i++) {
        int x, y; cin >> x >> y; x--; y--;
        played[x][y] = played[y][x] = true;
        won[x]++;
    }
    for(int i = 0; i < n; i++) {
        if(Check(i, played, won, n * (n - 1) / 2 - m)) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
    
    return 0;
}
