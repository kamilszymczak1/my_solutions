#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, int p, vector<vector<pair<int, bool>>>&adj, vector<pair<int, int>>&toAdd, vector<pair<int, int>>&toRemove, vector<bool>&parentErased) {
    int childrenCount = adj[x].size() - (p != -1);
    for(auto &[y, b] : adj[x]) {
        if(y != p) {
            DFS(y, x, adj, toAdd, toRemove, parentErased);
            if(parentErased[y] == true) {
                childrenCount--;
                b = true;
            }
        }
    }
    if(childrenCount >= 2) {
        if(p != -1) {
            parentErased[x] = true;
            toRemove.emplace_back(p + 1, x + 1);
            for(auto &[y, b] : adj[x]) {
                if(y == p) {
                    b = true;
                }
            }
        }
        for(int i = 0; i < adj[x].size() && childrenCount > 2; i++) {
            if(adj[x][i].first == p || parentErased[adj[x][i].first])
                continue;
            adj[x][i].second = true;
            for(auto &[y, b] : adj[adj[x][i].first]) {
                if(y == x) {
                    b = true;
                }
            }
            toRemove.emplace_back(adj[x][i].first + 1, x + 1);
            childrenCount--;
        }
    }
}

void DFS2(int x, vector<vector<pair<int, bool>>>&adj, vector<bool>&visited, int &end) {
    end = x;
    visited[x] = true;
    for(auto [y, b] : adj[x]) {
        if(b == true || visited[y])
            continue;
        DFS2(y, adj, visited, end);
    }
}

void TestCase() {
    int n; cin >> n;
    vector<vector<pair<int, bool>>>adj(n, vector<pair<int, bool>>());
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].emplace_back(b - 1, false);
        adj[b - 1].emplace_back(a - 1, false);
    }
    vector<pair<int, int>>toAdd, toRemove;
    vector<bool>parentErased(n, false), visited(n, false);
    DFS(0, -1, adj, toAdd, toRemove, parentErased);
    
    int leftEnd = -1;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            int currentLeft = i, currentRight = i;
            visited[i] = true;
            for(auto [y, b] : adj[i]) {
                if(b == false) {
                    if(currentLeft == i) {
                        DFS2(y, adj, visited, currentLeft);
                    } else {
                        DFS2(y, adj, visited, currentRight);
                    }
                }
            }
            if(leftEnd != -1) {
                toAdd.emplace_back(leftEnd + 1, currentRight + 1);
            }
            leftEnd = currentLeft;
        }
    }
    cout << toRemove.size() << '\n';
    for(int i = 0; i < toRemove.size(); i++) {
        cout << toRemove[i].first << ' ' << toRemove[i].second << ' ';
        cout << toAdd[i].first << ' ' << toAdd[i].second << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
