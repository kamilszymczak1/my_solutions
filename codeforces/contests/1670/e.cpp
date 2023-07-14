#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <map>

using namespace std;

void DFS(int x, int p, vector<vector<pair<int, int>>>&adj, vector<int>&nodeLabel, vector<int>&edgeLabel, int &last, int depth) {
    for(auto [y, edgeID] : adj[x]) {
        if(y == p)
            continue;
        edgeLabel[edgeID] = last;
        nodeLabel[y] = last + adj.size();
        if(depth == 0)
            swap(edgeLabel[edgeID], nodeLabel[y]);
        last++;
        DFS(y, x, adj, nodeLabel, edgeLabel, last, depth ^ 1);
    }
}

void TestCase() {
    int p; scanf("%d", &p);
    int n = 1 << p;
    vector<vector<pair<int, int>>>adj(n);
    for(int i = 0; i < n - 1; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].emplace_back(y - 1, i);
        adj[y - 1].emplace_back(x - 1, i);
    }
    
    int root = 0;
    for(int i = 0; i < n; i++)
        root = adj[i].size() == 1 ? i : root;
    vector<int>nodeLabel(n), edgeLabel(n - 1);
    nodeLabel[root] = n;
    int last = 1;
    DFS(root, -1, adj, nodeLabel, edgeLabel, last, 0);
    
    printf("%d\n", root + 1);
    for(int x : nodeLabel)
        printf("%d ", x);
    printf("\n");
    for(int x : edgeLabel)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
