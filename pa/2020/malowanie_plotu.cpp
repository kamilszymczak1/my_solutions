#include <iostream>
#include <vector>
using namespace std;
long long n, m, p;
vector<long long>dp[3];
int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> p;
    for(int i = 0; i < 3; i++) {
        dp[i].reserve(m + 7);
        dp[i].resize(m + 7, 0);
    }
    for(long long i = 0; i <= m; i++)
        dp[1][i] = ((i * (i + 1)) >> 1) % p;
    for(int i = 1; i < n; i++) {
        swap(dp[0], dp[1]);
        dp[1][0] = 0;
        for(int j = 1; j <= m; j++)
            dp[2][j] = (dp[2][j - 1] + dp[0][j]) % p;
        for(long long j = 1; j <= m; j++) {
            long long toAdd = (j * ((dp[0][m] - dp[0][m - j] + p) % p)) % p;
            dp[1][j] = (dp[1][j - 1] + toAdd - dp[2][j - 1] + p) % p;
        }
    }
    cout << dp[1][m] << '\n';
    return 0;
}
