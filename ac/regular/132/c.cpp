#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 998244353;
const int MAX_N = 507;

long long dp[MAX_N][1 << 11];

int main() {
    ios_base::sync_with_stdio(0);
    int n, d; cin >> n >> d;
    int bits = 2 * d + 1;
    vector<bool>usedValue(n + 1);
    vector<int>a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] != -1)
            usedValue[a[i]] = true;
    }
    
    dp[0][0] = 1;
    
    for(int i = 1; i <= n; i++) {
        if(a[i] == -1) {
            for(int chosen = max(1, i - d); chosen <= min(n, i + d); chosen++) {
                if(usedValue[chosen])
                    continue;
                int bit = chosen - i + d;
                for(int prevMask = 0; prevMask < (1 << bits); prevMask++) {
                    int newMask = prevMask >> 1;
                    if((newMask & (1 << bit)) == 0) {
                        dp[i][newMask ^ (1 << bit)] += dp[i - 1][prevMask];
                        dp[i][newMask ^ (1 << bit)] %= mod;
                    }
                }
            }
        } else {
            int bit = a[i] - i + d;
            for(int prevMask = 0; prevMask < (1 << bits); prevMask++) {
                int newMask = prevMask >> 1;
                if((newMask & (1 << bit)) == 0) {
                    dp[i][newMask ^ (1 << bit)] += dp[i - 1][prevMask];
                    dp[i][newMask ^ (1 << bit)] %= mod;
                }
            }
        }
    }
    
    long long result = 0;
    for(int mask = 0; mask < (1 << bits); mask++)
        result = (result + dp[n][mask]) % mod;
    cout << result << '\n';
    
    return 0;
}
