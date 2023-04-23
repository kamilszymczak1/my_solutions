#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int inf = 1 << 30;

int main() {
    int n, m, a; scanf("%d%d%d", &n, &m, &a);
    vector<vector<int>>dp(m + 1, vector<int>(2 * m + 1, inf));
    for(int i = a - m; i <= a; i++)
        dp[a - i][i + m] = 0;
    
    for(int i = 2; i <= n; i++) {
        
        for(int j = (int)dp.size() - 2; j >= 0; j--) {
            for(int k = 0; k <= 2 * m; k++) {
                dp[j][k] = min(dp[j][k], dp[j + 1][k]);
            }
        }
        
        vector<vector<int>>newDp(m / i + 1, vector<int>(2 * m + 1, inf));
        int a; scanf("%d", &a);
        
        for(int next = 0; next <= m / i; next++) {
            for(int rem1 = -m; rem1 <= m; rem1++) {
                int rem0 = rem1 + next - a;
                if(rem0 < -m || rem0 > m)
                    continue;
                newDp[next][rem1 + m] = min(newDp[next][rem1 + m], dp[next][rem0 + m] + abs(rem0));
            }
        }
        
        swap(dp, newDp);
    }
    
    int result = inf;
    for(int i = 0; i <= m / n; i++)
        result = min(result, dp[i][m + 0]);
    printf("%d\n", result);
    
    return 0;
}
