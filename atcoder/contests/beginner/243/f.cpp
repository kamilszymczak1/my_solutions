#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long mod = 998244353;
const int MAX_N = 57;

long long ModPow(int x, int exp) {
    if(exp == 0)
        return 1;
    long long result = ModPow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

long long Inv(long long x) {
    return ModPow(x, mod - 2);
}

long long dp[MAX_N][MAX_N][MAX_N], choose[MAX_N][MAX_N];
long long w[MAX_N], W = 0;

int main() {
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 0; i < N; i++) {
        scanf("%lld", &w[i]);
        W += w[i];
    }
    choose[0][0] = 1;
    for(int i = 1; i < MAX_N; i++) {
        choose[i][0] = 1;
        for(int j = 1; j <= i; j++)
            choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % mod;
    }
    
    W = Inv(W);
    for(int i = 0; i < N; i++)
        w[i] = (w[i] * W) % mod;
    
    dp[0][0][0] = 1;
    for(int i = 1; i <= N; i++) {
        for(int j = 0; j <= K; j++) {
            for(int t = 0; t <= j; t++) {
                for(int k = 0; k <= M; k++) {
                    if(t != 0 && k == 0)
                        continue;
                    int prevK = t == 0 ? k : (k - 1);
                    long long A = dp[i - 1][j - t][prevK] * ModPow(w[i - 1], t) % mod;
                    dp[i][j][k] += A * choose[j][t];
                    dp[i][j][k] %= mod;
                }
            }
        }
    }
    
    printf("%lld\n", dp[N][K][M]);
    
    return 0;
}
