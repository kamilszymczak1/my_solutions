#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const vector<pair<int, int>>moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void DFS(int i, int j, vector<vector<bool>>&grid, vector<pair<int, int>>&v) {
    int n = grid.size(), m = grid[0].size();
    grid[i][j] = 0;
    v.emplace_back(i, j);
    for(auto [x, y] : moves) {
        int I = i + x, J = j + y;
        if(0 <= I && I < n && 0 <= J && J < m && grid[I][J] == 1) {
            DFS(I, J, grid, v);
        }
    }
}

void TestCase() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<bool>>grid(n, vector<bool>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; do c = getchar(); while(c != '0' && c != '1');
            grid[i][j] = c - '0';
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j]) {
                vector<pair<int, int>>v;
                DFS(i, j, grid, v);
                int l = m, r = 0, b = 0, t = n;
                for(auto [x, y] : v) {
                    l = min(l, y);
                    r = max(r, y);
                    b = max(b, x);
                    t = min(t, x);
                }
                int size = (r - l + 1) * (b - t + 1);
                if(size != v.size()) {
                    printf("NO\n");
                    return;
                }
            }
        }
    }
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
