#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

struct seg_tree { 
    vector<int>values;
    int leaf_count;
    seg_tree(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values.resize(leaf_count * 2, 0);
    }
    void add(int x, int y, int value) {
        x += leaf_count; y += leaf_count;
        values[x] += value;
        if(x != y)
            values[y] += value;
        for(; x / 2 != y / 2; x /= 2, y /= 2) {
            if(x % 2 == 0)
                values[x + 1] += value;
            if(y % 2 == 1)
                values[y - 1] += value;
        }
    }
    int get(int x) {
        int result = 0;
        for(x += leaf_count; x; x /= 2)
            result += values[x];
        return result;
    }
};

const int MAX_N = 100'007;
vector<int> adj[MAX_N], jump[MAX_N];
int pre[MAX_N], post[MAX_N], t = -1;
int n, m, f[MAX_N], depth[MAX_N];

int dsu_find(int x) { return f[x] == x ? x : f[x] = dsu_find(f[x]); }
void dsu_union(int x, int y) { f[dsu_find(x)] = dsu_find(y); }

void DFS(int x, int p) {
    if(p != -1) {
        jump[x].push_back(p);
        for(int i = 0; i < (int)jump[x].size(); i++) {
            if(i < (int)jump[jump[x][i]].size()) {
                jump[x].push_back(jump[jump[x][i]][i]);
            }
        }
    }
    pre[x] = ++t;
    for(int y : adj[x]) {
        if(y != p) {
            depth[y] = depth[x] + 1;
            DFS(y, x);
        }
    }
    post[x] = t;
}

void TestCase() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++)
        f[i] = i;
    vector<pair<int, int>>spare_edges;
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y); x--; y--;
        if(dsu_find(x) != dsu_find(y)) {
            dsu_union(x, y);
            adj[x].push_back(y);
            adj[y].push_back(x);
        } else {
            spare_edges.emplace_back(x, y);
        }
    }
    DFS(0, -1);
    
    seg_tree T(n);
    for(auto [x, y] : spare_edges) {
        if(depth[x] < depth[y])
            swap(x, y);
        if(pre[y] <= pre[x] && pre[x] <= post[y]) {
            T.add(0, n - 1, 1);
            T.add(pre[x], post[x], 1);
            for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
                if(i < (int)jump[x].size() && depth[jump[x][i]] > depth[y]) {
                    x = jump[x][i];
                }
            }
            T.add(pre[x], post[x], -1);
        } else {
            T.add(pre[x], post[x], 1);
            T.add(pre[y], post[y], 1);
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(T.get(pre[i]) == (int)spare_edges.size()) {
            putchar('1');
        } else {
            putchar('0');
        }
    }
    putchar('\n');
}

int main() {
    TestCase();
    return 0;
}
