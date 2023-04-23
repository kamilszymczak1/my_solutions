#include <iostream>

using namespace std;

constexpr int MAX_N = 1000;
constexpr long long MOD = 998244353;

long long dp1[MAX_N][MAX_N], dp2[MAX_N][MAX_N];

int divisors(int x) {
    int result = 0;
    for(int i = 1; i <= x; i++)
        if(x % i == 0)
            result++;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    dp2[1][1] = 1;
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j < 2 * i; j++) {
            dp1[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
        }
        long long sum = 0;
        for(int j = 1; j < 2 * (i - 1); j++)
            sum = (sum + dp[i - 1]
        for(int j = 1; j < 2 * i; j++) {
            if(i % j == 0)
                dp[i][j]++;
        }
        dp[i][i * 2 - 1] += sum;
        dp[i][i * 2 - 1] %= MOD;
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < n * 2; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
    
    long long sum = 0;
    for(int i = 1; i < 2 * n; i++)
        sum = (sum + dp[n][i]) % MOD;
    cout << sum << '\n';
    return 0;
}
