#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200'000;

struct Edge {
    int to, a, b;
    Edge() {}
    Edge(int _to, int _a, int _b) : to(_to), a(_a), b(_b) {}
};

void DFS(int x, vector<vector<Edge>>&adj, vector<int>&r, vector<long long>&current, long long A) {
    r[x] = upper_bound(current.begin(), current.end(), A) - current.begin() - 1;
    for(Edge e : adj[x]) {
        current.push_back(current.back() + e.b);
        DFS(e.to, adj, r, current, A + e.a);
        current.pop_back();
    }
}

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<Edge>>adj(n);
    for(int i = 1; i < n; i++) {
        int p, a, b; scanf("%d%d%d", &p, &a, &b);
        adj[p - 1].emplace_back(i, a, b);
    }
    vector<int>r(n);
    vector<long long>current(1, 0);
    DFS(0, adj, r, current, 0);
    for(int i = 1; i < n; i++)
        printf("%d ", r[i]);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
