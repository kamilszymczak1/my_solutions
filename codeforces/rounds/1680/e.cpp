#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

char c[200'007];

int inf = 1 << 25;

void TestCase() {
    int n; scanf("%d", &n);
    vector<vector<char>>grid(2, vector<char>(n + 2));
    for(int i = 0; i < 2; i++) {
        scanf("%s", c);
        for(int j = 1; j <= n; j++)
            grid[i][j] = c[j - 1];
    }
    grid[0][0] = grid[1][0] = grid[0][n + 1] = grid[1][n + 1] = '.';
    
    vector<vector<int>>dp1(2, vector<int>(n + 2, inf)), dp2(2, vector<int>(n + 2, inf));
    int k1 = 0;
    while(grid[0][k1] != '*' && grid[1][k1] != '*')
        k1++;
    dp1[0][k1] = grid[1][k1] == '*' ? 1 : 0;
    dp1[1][k1] = grid[0][k1] == '*' ? 1 : 0;
    for(int i = k1 + 1; i <= n; i++) {
        //dp1[0][i]
        if(grid[1][i] == '*') {
            dp1[0][i] = min(dp1[1][i - 1] + 2, dp1[0][i - 1] + 2);
        } else {
            dp1[0][i] = min(dp1[1][i - 1] + 2, dp1[0][i - 1] + 1);
        }
        
        if(grid[0][i] == '*') {
            dp1[1][i] = min(dp1[0][i - 1] + 2, dp1[1][i - 1] + 2);
        } else {
            dp1[1][i] = min(dp1[0][i - 1] + 2, dp1[1][i - 1] + 1);
        }
    }
    
    int k2 = n + 1;
    while(grid[0][k2] != '*' && grid[1][k2] != '*')
        k2--;
    dp2[0][k2] = grid[1][k2] == '*' ? 1 : 0;
    dp2[1][k2] = grid[0][k2] == '*' ? 1 : 0;
    for(int i = k2 - 1; i >= 0; i--) {
        if(grid[1][i] == '*') {
            dp2[0][i] = min(dp2[1][i + 1] + 2, dp2[0][i + 1] + 2);
        } else {
            dp2[0][i] = min(dp2[1][i + 1] + 2, dp2[0][i + 1] + 1);
        }
        
        if(grid[0][i] == '*') {
            dp2[1][i] = min(dp2[0][i + 1] + 2, dp2[1][i + 1] + 2);
        } else {
            dp2[1][i] = min(dp2[0][i + 1] + 2, dp2[1][i + 1] + 1);
        }
    }
    
    int ans = min(min(dp1[0][k2], dp1[1][k2]), min(dp2[0][k1], dp2[1][k1]));
    
    for(int i = k1; i < k2; i++) {
        ans = min(ans, dp1[0][i] + dp2[0][i + 1] + 1);
        ans = min(ans, dp1[1][i] + dp2[1][i + 1] + 1);
        ans = min(ans, dp1[1][i] + dp2[0][i + 1] + 2);
        ans = min(ans, dp1[0][i] + dp2[1][i + 1] + 2);
    }
    printf("%d\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
