#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long mod = 1000000007;

long long ModPow(int x, int exp) {
    if(exp == 0)
        return 1;
    long long result = ModPow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

void TestCase() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<long long>>dp(n + 1, vector<long long>(n + 1, 0));
    long long rev2 = ModPow(2, mod - 2);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < i; j++)
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) * rev2 % mod;
        dp[i][i] = i;
    }
    cout << (dp[n][m] * k) % mod << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}

