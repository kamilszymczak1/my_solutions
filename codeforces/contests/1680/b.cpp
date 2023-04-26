#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

char c[100000];

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    int firstColumn = m, firstRow = n;
    vector<vector<char>>grid(n, vector<char>(m));
    for(int i = 0; i < n; i++) {
        scanf("%s", c);
        for(int j = 0; j < m; j++) {
            grid[i][j] = c[j];
            if(grid[i][j] == 'R') {
                firstColumn = min(firstColumn, j);
                firstRow = min(firstRow, i);
            }
        }
    }
    
    if(firstColumn == m) {
        printf("NO\n");
    } else if(grid[firstRow][firstColumn] == 'R') {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
