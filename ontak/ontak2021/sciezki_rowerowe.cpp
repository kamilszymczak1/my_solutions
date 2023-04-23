#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e9 + 8;

void DFSNodes(int x, vector<vector<int>>&adj, vector<bool>&visited, vector<int>&nodes) {
    visited[x] = true;
    nodes.push_back(x);
    for(int y : adj[x]) {
        if(!visited[y]) {
            DFSNodes(y, adj, visited, nodes);
        }
    }
}

void Load(vector<vector<int>>&distance, vector<int>&specialNodes) {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>>specialAdj(n);
    vector<vector<pair<int, int>>>inputAdj(n);
    for(int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        specialAdj[a - 1].push_back(b - 1);
        specialAdj[b - 1].push_back(a - 1);
    }
    for(int i = 0; i < m - k; i++) {
        int a, b, c; cin >> a >> b >> c;
        inputAdj[a - 1].emplace_back(b - 1, c);
        inputAdj[b - 1].emplace_back(a - 1, c);
    }
    vector<bool>visited(n, false);
    vector<int>resultIndex(n, -1);
    int  currentIndex = 0;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            if(specialAdj[i].size() != 0) {
                vector<int>nodes;
                DFSNodes(i, specialAdj, visited, nodes);
                for(int x : nodes)
                    resultIndex[x] = currentIndex;
                specialNodes.push_back(currentIndex);
            } else {
                resultIndex[i] = currentIndex;
            }
            currentIndex++;
        }
    }
    distance.resize(currentIndex, vector<int>(currentIndex, inf));
    for(int i = 0; i < n; i++) {
        for(pair<int, int>&p : inputAdj[i]) {
            distance[resultIndex[i]][resultIndex[p.first]] = min(distance[resultIndex[i]][resultIndex[p.first]], p.second);
        }
    }
    for(int i = 0; i < currentIndex; i++)
        distance[i][i] = 0;
}

void CalcMinDist(vector<vector<int>>&distance) {
    int n = distance.size();
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    vector<vector<int>>distance;
    vector<int>specialNodes;
    Load(distance, specialNodes);
    CalcMinDist(distance);
    int n = distance.size(), k = specialNodes.size();
    
    vector<vector<int>>dp(n, vector<int>(1 << k, inf));
    
    for(int i = 0; i < k; i++) {
        dp[specialNodes[i]][1 << i] = 0;
    }
    
    for(int mask = 1; mask < (1 << k); mask++) {
        for(int i = 0; i < n; i++) {
            for(int submask = (mask - 1) & mask; submask; submask = (submask - 1) & mask) {
                dp[i][mask] = min(dp[i][mask], dp[i][submask] + dp[i][mask ^ submask]);
            }
        }
        vector<int>dp2(n, inf);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dp2[i] = min(dp2[i], dp[j][mask] + distance[i][j]);
            }
        }
        for(int i = 0; i < n; i++)
            dp[i][mask] = dp2[i];
    }
    
    int result = inf;
    for(int i = 0; i < n; i++)
        result = min(result, dp[i][(1 << k) - 1]);
    cout << result << '\n';
    
    return 0;
}

/*
6 8 2
1 3
2 6
1 5 2
6 1 5
2 5 2
3 4 1
5 3 2
5 6 3
*/
