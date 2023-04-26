#include <iostream>
using namespace std;
const int MAX_N = 2007;
int dp[2][MAX_N][MAX_N], maxR[MAX_N][MAX_N], n, m;
int pref[2][MAX_N][MAX_N];
char grid[MAX_N][MAX_N];
int main() {
ios_base::sync_with_stdio(0);
cin >> n >> m;
for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++)
        cin >> grid[i][j];
    
    for(int j = 0; j < m; j++) {
        pref[0][0][j] = 1;
        for(int i = 1; i < n; i++)
            pref[0][i][j] = grid[i][j] == grid[i - 1][j] ? pref[0][i - 1][j] + 1 : 1;
        pref[1][n - 1][j] = 1;
        for(int i = n - 2; i >= 0; i--)
            pref[1][i][j] = grid[i][j] == grid[i + 1][j] ? pref[1][i + 1][j] + 1 : 1;
        for(int i = 0; i < n; i++)
            maxR[i][j] = min(pref[0][i][j], pref[1][i][j]);
    }
    
    for(int i = 0; i < n; i++) {
        dp[0][i][0] = 1;
        for(int j = 1; j < m; j++)
            dp[0][i][j] = grid[i][j] == grid[i][j - 1] ? min(maxR[i][j], dp[0][i][j - 1] + 1) : 1;
        dp[1][i][m - 1] = 1;
        for(int j = m - 2; j >= 0; j--)
            dp[1][i][j] = grid[i][j] == grid[i][j + 1] ? min(maxR[i][j], dp[1][i][j + 1] + 1) : 1;
    }
    
    long long result = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            result += min(dp[0][i][j], dp[1][i][j]);
        
        cout << result << '\n';
    return 0;
}
