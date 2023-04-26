#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

void DFS(int x, int p, vector<vector<int>>&adj, vector<bool>&b) {
    for(int y : adj[x]) {
        if(y != p) {
            b[y] = b[x] ^ 1;
            DFS(y, x, adj, b);
        }
    }
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<vector<int>>adj(n);
    for(int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    vector<bool>b(n);
    DFS(0, -1, adj, b);
    for(int i = 0; i < n; i++) {
        int x = ((int)adj[i].size()) * (2 * (int)b[i] - 1);
        printf("%d ", x);
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
