#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int B = 30;
const int MAX_N = 100'007;
int f[B][MAX_N], visited[MAX_N];
vector<pair<int, int>>adj[B][MAX_N];

int Find(int x, int j) {
    return f[j][x] == x ? x : f[j][x] = Find(f[j][x], j);
}

void Union(int x, int y, int j) {
    f[j][Find(x, j)] = Find(y, j);
}

void DFS(int x, int j, vector<int>&nodes) {
    nodes.push_back(x);
    visited[x] = true;
    for(auto [y, w] : adj[j][x]) {
        if(visited[y] || w != 3)
            continue;
        DFS(y, j, nodes);
    }
}

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    for(int i = 0; i < B; i++) {
        for(int j = 0; j < n; j++) {
            f[i][j] = j;
        }
    }
    for(int i = 0; i < m; i++) {
        int a, b, w; scanf("%d%d%d", &a, &b, &w); a--; b--;
        for(int bit = 0; bit < B; bit++) {
            if((w >> bit) & 1) {
                Union(a, b, bit);
            }
        }
        
        for(int bit = 1; bit < B; bit++) {
            adj[bit][a].emplace_back(b, ((w >> bit) & 1) * 2 + (w & 1));
            adj[bit][b].emplace_back(a, ((w >> bit) & 1) * 2 + (w & 1));
        }
    }
    
    vector<bool>ok(n, false);
    for(int bit = 1; bit < B; bit++) {
        fill(visited, visited + n, false);
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                vector<int>nodes;
                DFS(i, bit, nodes);
                bool OK = false;
                for(int x : nodes) {
                    for(auto [y, w] : adj[bit][x]) {
                        OK |= w == 0 || w == 2;
                    }
                }
                for(int x : nodes) {
                    ok[x] = ok[x] | OK;
                }
            }
        }
    }
    
    
    int q; scanf("%d", &q);
    for(int i = 0; i < q; i++) {
        int a, b; scanf("%d%d", &a, &b); a--; b--;
        int ans = ok[a] ? 1 : 2;
        for(int bit = 0; bit < B; bit++) {
            if(Find(a, bit) == Find(b, bit)) {
                ans = 0;
            }
        }
        printf("%d\n", ans);
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
