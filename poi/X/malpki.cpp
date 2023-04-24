#include <algorithm>
#include <cstdio>
#include <vector>
const int MAX_N = 200007;
int adj[MAX_N][2], fallTime[MAX_N], q[MAX_N << 1][2], s[MAX_N], n, m;
bool erased[MAX_N][2], visited[MAX_N];
std::vector<int>graph[MAX_N];
int Find(int x) {
    if(s[x] == -1)
        return x;
    return s[x] = Find(s[x]);
}
void Union(int x, int y) {
    x = Find(x); y = Find(y);
    if(x != y)
        s[x] = y;
}
void DFS(int x, int t) {
    Union(x, 0);
    visited[x] = true;
    fallTime[x] = t;
    for(int y : graph[x])
        if(!visited[y])
            DFS(y, t);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            scanf("%d", &adj[i][j]);
            adj[i][j] = std::max(-1, adj[i][j] - 1);
        }
    }
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &q[i][0], &q[i][1]);
        erased[--q[i][0]][--q[i][1]] = 1;
    }
    for(int i = 0; i < n; i++) {
        if(!erased[i][0] && adj[i][0] != -1) {
            graph[i].push_back(adj[i][0]);
            graph[adj[i][0]].push_back(i);
        }
        if(!erased[i][1] && adj[i][1] != -1) {
            graph[i].push_back(adj[i][1]);
            graph[adj[i][1]].push_back(i);
        }
    }
    std::fill(s, s + n, -1);
    DFS(0, -1);
    for(int i = m - 1; i >= 0; i--) {
        int a = Find(q[i][0]), b = Find(adj[q[i][0]][q[i][1]]);
        if(a != b) {
            if(a == 0)
                DFS(b, i);
            if(b == 0)
                DFS(a, i);
            Union(a, b);
        }
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 0; i < n; i++)
        printf("%d\n", fallTime[i]);
    return 0;
}
