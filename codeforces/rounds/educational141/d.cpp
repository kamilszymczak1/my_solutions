#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 307;
const int T = MAX_N * MAX_N;

const long long mod = 998244353;

int dp[2][2 * T + 1];

int main() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    dp[0][a[1] + T] = 1;
    
    for(int i = 2; i < n; i++) {
        fill(dp[1], dp[1] + 2 * T + 1, 0);
        for(int j = -T; j <= T; j++) {
            
            if(j == 0) {
                dp[1][a[i] + T] += dp[0][j + T];
                if(dp[1][a[i] + T] >= mod)
                    dp[1][a[i] + T] -= mod;
            } else {
                
                if(a[i] + j + T <= 2 * T && a[i] + j + T >= 0) {
                    dp[1][a[i] + j + T] += dp[0][j + T];
                    if(dp[1][a[i] + j + T] >= mod)
                        dp[1][a[i] + j + T] -= mod;
                }
                
                if(a[i] - j + T >= 0 && a[i] - j + T <= 2 * T) {
                    dp[1][a[i] - j + T] += dp[0][j + T];
                    if(dp[1][a[i] - j + T] >= mod)
                        dp[1][a[i] - j + T] -= mod;
                }
 
            }
            
        }
        swap(dp[0], dp[1]);
    }
    
    int answer = 0;
    for(int i = 0; i <= 2 * T; i++) {
        answer += dp[0][i];
        if(answer >= mod)
            answer -= mod;
    }
    printf("%d\n", answer);
    
    return 0;
}
