#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long mod = 998244353;
const int MAX_N = 257;
long long dp[MAX_N][MAX_N], choose[MAX_N][MAX_N], P[MAX_N][MAX_N * MAX_N];

void TestCase() {
    int N, K; scanf("%d%d", &N, &K);
    for(int i = 0; i <= N; i++) {
        choose[i][0] = 1;
        for(int j = 1; j <= i; j++)
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
    }
    for(int i = 0; i <= K; i++) {
        P[i][0] = 1;
        for(int j = 1; j <= N * (N - 1) / 2; j++)
            P[i][j] = (P[i][j - 1] * i) % mod;
    }
    dp[1][0] = 1;
    for(int i = 1; i < N; i++) {
        for(int k = 1; k <= K; k++)
            dp[i][k] = (dp[i][k] + dp[i][k - 1]) % mod;
        for(int nextK = 1; nextK <= K; nextK++) {
            long long p = 0;
            for(int j = 1; i + j <= N; j++) {
                p += i + j - 2;
                long long toAdd = dp[i][nextK - 1] * P[K - nextK + 1][p] % mod;
                toAdd = toAdd * choose[i + j - 1][j] % mod;
                dp[i + j][nextK] += toAdd;
                dp[i + j][nextK] %= mod;
            }
        }
    }
    long long result = 0;
    for(int k = 1; k <= K; k++)
        result += dp[N][k];
    printf("%lld\n", result % mod);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
