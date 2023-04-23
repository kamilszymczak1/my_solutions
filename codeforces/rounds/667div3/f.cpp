#include <cstdio>
#include <vector>

using namespace std;

char c[201], s[3];

const int inf = 1 << 30;

int main() {
    int n, k; scanf("%d%d", &n, &k);
    scanf("%s%s", c, s);
    vector<vector<int>>dp(n + 1, vector<int>(k + 1, -inf));
    dp[0][0] = 0;
    for(int t = 0; t < n; t++) {
        vector<vector<int>>newDp(n + 1, vector<int>(k + 1, -inf));
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= k; j++) {
                if(c[t] == s[0] && c[t] == s[1] && i + 1 <= n)
                    newDp[i + 1][j] = max(newDp[i + 1][j], dp[i][j] + i);
                
                if(c[t] == s[0] && c[t] != s[1] && i + 1 <= n)
                    newDp[i + 1][j] = max(newDp[i + 1][j], dp[i][j]);
                
                if(c[t] != s[0] && c[t] == s[1])
                    newDp[i][j] = max(newDp[i][j], dp[i][j] + i);
                
                //we change c[i] to s[0]
                if(i + 1 <= n && j + 1 <= k)
                    newDp[i + 1][j + 1] = max(newDp[i + 1][j + 1], dp[i][j]);
                
                //we change c[i] to s[1]
                if(j + 1 <= k)
                    newDp[i][j + 1] = max(newDp[i][j + 1], dp[i][j] + i);
                
                //is s[0] == s[1] they both happen at the same time
                if(s[0] == s[1] && i + 1 <= n && j + 1 <= k)
                    newDp[i + 1][j + 1] = max(newDp[i + 1][j + 1], dp[i][j] + i);
                
                newDp[i][j] = max(newDp[i][j], dp[i][j]);
            }
        }
        
        swap(newDp, dp);
    }
    
    int ans = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    printf("%d\n", ans);
}
