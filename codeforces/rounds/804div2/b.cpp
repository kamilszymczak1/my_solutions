#include <cstdio>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<int>>grid(n, vector<int>(m));
    for(int i = 0; i < n / 2; i++) {
        for(int j = 0; j < m / 2; j++) {
            if((i + j) % 2) {
                grid[i * 2][j * 2] = 0;
                grid[i * 2 + 1][j * 2] = 1;
                grid[i * 2][j * 2 + 1] = 1;
                grid[i * 2 + 1][j * 2 + 1] = 0;
            } else {
                grid[i * 2][j * 2] = 1;
                grid[i * 2 + 1][j * 2] = 0;
                grid[i * 2][j * 2 + 1] = 0;
                grid[i * 2 + 1][j * 2 + 1] = 1;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
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

