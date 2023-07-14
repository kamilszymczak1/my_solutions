#include <cstdio>
#include <vector>

using namespace std;

const int inf = 1 << 30;

int main() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int answer = inf;
    for(int k = 0; k < 2; k++) {
        vector<vector<int>>dp(n, vector<int>(2, inf));
        dp[0][0] = 0;
        dp[0][1] = 1;
        for(int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][1];
            if(i % 2 == k) {
                if(a[i - 1] < a[i]) {
                    dp[i][0] = min(dp[i][0], dp[i - 1][0]);
                } else {
                    dp[i][0] = min(dp[i][0], dp[i - 1][0] + 1);
                }
            } else {
                if(a[i - 1] > a[i]) {
                    dp[i][0] = min(dp[i][0], dp[i - 1][0]);
                } else {
                    dp[i][0] = min(dp[i][0], dp[i - 1][0] + 1);
                }
            }
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
        }
        answer = min(answer, dp[n - 1][0]);
        answer = min(answer, dp[n - 1][1]);
    }
    
    printf("%d\n", answer);
    
    return 0;
}
