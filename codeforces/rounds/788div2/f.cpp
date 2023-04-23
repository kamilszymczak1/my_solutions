#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <map>

using namespace std;

const long long mod = 1'000'000'007;
const int B = 60;

int Solve(int n, long long r, long long z) {
    
    vector<vector<int>>C(n + 1, vector<int>(n + 1));
    for(int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
            if(C[i][j] >= mod)
                C[i][j] -= mod;
        }
    }
    
    r++;
    
    int ans = 0;
    
    vector<vector<int>>DP(B + 1, vector<int>(1, 0));
    DP[0][0] = 1;
    for(int i = 0; i < B; i++) {
        DP[i + 1].resize(min((long long)n, r / (1ll << (i + 1))) + 1);
        for(long long x = 0; x < (int)DP[i].size(); x++) {
            for(long long y = (z >> i) & 1; (x + y) / 2 < (int)DP[i + 1].size() && y <= n; y += 2) {
                DP[i + 1][(x + y) / 2] = (DP[i + 1][(x + y) / 2] + 1ll * DP[i][x] * C[n][y]) % mod;
            }
        }
    }

    for(int diff = 0; diff < B; diff++) {
        if(((r >> diff) & 1) == 0)
            continue;
        vector<vector<int>>dp(B + 1, vector<int>(1, 0));
        dp[diff + 1].resize(min((long long)n, r / (1ll << (diff + 1))) + 1);
        for(long long x = (z >> diff) & 1; x < (int)DP[diff].size(); x += 2) {
            for(long long y = (z >> diff) & 1; (x + y) / 2 < (int)dp[diff + 1].size() && y <= n; y += 2) {
                dp[diff + 1][(x + y) / 2] = (dp[diff + 1][(x + y) / 2] + 1ll * DP[diff][x] * C[n][y]) % mod;
            }
        }
        for(int i = diff + 1; i < B; i++) {
            dp[i + 1].resize(min((long long)n, r / (1ll << (i + 1))) + 1);
            for(long long x = ((z >> i) & 1) ^ ((r >> i) & 1); x < (int)dp[i].size(); x += 2) {
                for(long long y = (z >> i) & 1; (x + y) / 2 < (int)dp[i + 1].size() && y <= n; y += 2) {
                    dp[i + 1][(x + y) / 2] = (dp[i + 1][(x + y) / 2] + 1ll * dp[i][x] * C[n][y]) % mod;
                }
            }
        }
        ans += dp[B][0];
        if(ans >= mod)
            ans -= mod;
    }
    return ans;
}

void TestCase() {
    int n; scanf("%d", &n);
    long long l, r, z; scanf("%lld%lld%lld", &l, &r, &z);
    printf("%lld\n", (Solve(n, r, z) - Solve(n, l - 1, z) + mod) % mod);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
}
