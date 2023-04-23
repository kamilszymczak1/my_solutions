#include <iostream>
#include <vector>

using namespace std;

constexpr long long mod = 1000000007;

void TestCase() {
    int n, k; cin >> n >> k;
    vector<long long>dp(n + 1, 0);
    vector<long long>factorial(n + 1, 1);
    for(long long i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    long long sum = 0, result = 0;
    long long t = 0;
    for(int i = 0; i < n; i++) {
        t += min(i, k - 1) + min(k - 1, n - i - 1);
    }
    for(int i = 2; i <= n; i++) {
        dp[i] = t * factorial[n - 2] / factorial[n - i];
        sum += dp[i];
        result += dp[i] * i;
        cout << "dp = " << dp[i] << '\n';
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
