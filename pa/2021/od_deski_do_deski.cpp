#include <iostream>

using namespace std;

const long long mod = 1'000'000'007;
const int MAX_N = 3007;

long long dp[MAX_N][MAX_N][2];
//dp[i][j][k][l]
//i -> length
//j -> #active colours
//k -> is the last one active?
int n, m;

int Solve() {
    cin >> n >> m;
    dp[0][0][1] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= i; j++) {
            long long activeColours = j;
            long long idleColours = m - j;
            
            //1 -> the last one is active
            //1a -> we put an idle colour so it becomes active
            dp[i + 1][j + 1][0] += dp[i][j][1] * idleColours;
            dp[i + 1][j + 1][0] %= mod;
            //1b -> we put and active colour
            dp[i + 1][j][1] += dp[i][j][1] * activeColours;
            dp[i + 1][j][1] %= mod;
            
            
            //2 -> the last one is idle
            //2a -> we put an idle colour
            dp[i + 1][j][0] += dp[i][j][0] * idleColours;
            dp[i + 1][j][0] %= mod;
            //2b -> we put an active colour
            dp[i + 1][j][1] += dp[i][j][0] * activeColours;
            dp[i + 1][j][1] %= mod;
        }
    }
    
    long long result = 0;
    for(int i = 1; i <= n; i++)
        result = (result + dp[n][i][1]) % mod;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout << Solve() << '\n';
    
    return 0;
}
