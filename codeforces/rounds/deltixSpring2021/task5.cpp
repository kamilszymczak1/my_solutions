#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, k; cin >> n >> k;
    vector<long double>dp(n + 1, 0);
    dp[0] = 0, dp[1] = 1, dp[2] = 2;
    for(int i = 3; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            int left = min(k - 1, j - 1);
            int right = min(k - 1, i - j);
            int a = max(0, j - left - 1);
            int b = max(0, i - j - right);
            cout << (left + right + a * dp[a] + b * dp[b]) / (i * 1.0) << '\n';
            dp[i] += (left + right + a * dp[a] + b * dp[b]) / (i * 1.0);
        }
    }
    cout << dp[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
