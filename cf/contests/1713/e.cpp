#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cmath>
#include <cstring>

using namespace std;

struct DSU {
    vector<int>f, color;
    vector<vector<int>>group;
    DSU(int n) {
        f.resize(n);
        color.resize(n, 0);
        group.resize(n);
        for(int i = 0; i < n; i++) {
            f[i] = i;
            group[i].push_back(i);
        }
    }
    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    bool merge(int x, int y, int t) {
        if(find(x) == find(y)) {
            return (color[x] ^ t) == color[y];
        } else {
            if((color[x] ^ t) == color[y]) {
                x = find(x), y = find(y);
                for(int z : group[y])
                    group[x].push_back(z);
                group[y].swap(*(new vector<int>()));
            } else {
                x = find(x), y = find(y);
                for(int z : group[y]) {
                    color[z] ^= 1;
                    group[x].push_back(z);
                }
                group[y].swap(*(new vector<int>()));
            }
            f[y] = x;
            return true;
        }
    }
};

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<int>>grid(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    DSU dsu(n);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(grid[i][j] > grid[j][i]) {
                dsu.merge(i, j, 1);
            } else if(grid[i][j] < grid[j][i]) {
                dsu.merge(i, j, 0);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(dsu.color[i] == 1) {
            for(int j = 0; j < n; j++) {
                swap(grid[i][j], grid[j][i]);
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
