#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 300'007;

int dp[2][MAX_N], a[MAX_N], pref[MAX_N], suff[MAX_N];

int main() {
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        pref[i] = pref[i - 1] + a[i];
    }
    for(int i = n; i > 0; i--)
        suff[i] = suff[i + 1] + a[i];
    int x = pref[n], y = pref[n];
    for(int i = 1; i <= n; i++) {
        if(a[i] == 0) {
            dp[0][i] = max(dp[0][i - 1] + 1, pref[i - 1] + 1);
            dp[1][i] = min(dp[1][i - 1] + 1, pref[i - 1] + 1);
        } else {
            dp[0][i] = max(dp[0][i - 1], pref[i - 1]);
            dp[1][i] = min(dp[1][i - 1], pref[i - 1]);
        }
       // printf("%d ", dp[0][i]);
        x = min(x, dp[1][i] + suff[i + 1]);
        y = max(y, dp[0][i] + suff[i + 1]);
    }
//     printf("\n");
//     for(int i = 1; i <= n; i++)
//         printf("%d ", dp[1][i]);
//     printf("\n");
    printf("%d\n", y - x + 1);
}
