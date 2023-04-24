#include <cstdio>

using namespace std;

int max(int a, int b) {
    if(a > b)
        return a;
    return b;
}

int min(int a, int b) {
    if(a < b)
        return a;
    return b;
}

const long long mod = 1'000'000'007;
const int MAX_N = 100'007;

int h[MAX_N], l[MAX_N], r[MAX_N], n;
long long dp[MAX_N][3][3];
bool appear[MAX_N];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        l[i] = 0;
        r[i] = n - 1;
    }
    
    int remaining = n;
    for(int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
        h[i]--;
        l[h[i]] = max(l[h[i]], i - 1);
        r[h[i]] = min(r[h[i]], i + 1);
        if(!appear[h[i]])
            remaining--;
        appear[h[i]] = true;
    }
    
    for(int i = 0; i < n; i++) {
        if(l[i] > r[i]) {
            printf("0\n");
            return 0;
        }
    }
    
    if(h[0] == h[1]) {
        dp[1][1][0] = 1;
        dp[1][2][1] = 1;
    } else {
        dp[1][1][1] = 1;
        dp[1][1][2] = 1;
        dp[1][2][0] = 1;
        dp[1][2][2] = 1;
    }
    
    for(int i = 2; i < n; i++) {
        if(h[i] == h[i - 1] && h[i] == h[i - 2]) {
            
            dp[i][1][0] = dp[i - 1][2][1];
        } else if(h[i] == h[i - 1]) {
            dp[i][1][0] = dp[i - 1][0][1] + dp[i - 1][1][1];
            dp[i][2][1] = dp[i - 1][0][2] + dp[i - 1][1][2] + dp[i - 1][2][2];
        } else if(h[i] == h[i - 2]) {
            dp[i][0][0] = dp[i - 1][2][0];
            dp[i][2][0] = dp[i - 1][2][2];
        } else {
            for(int j = 0; j < 3; j++) {
                for(int k = 0; k < 3; k++) {
                    if(j - 1 == k)
                        continue;
                    for(int l = 0; l < 3; l++) {
                        if(l == 2 && k == 0)
                            continue;
                        dp[i][j][k] += dp[i - 1][l][j];
                    }
                        
                }
            }
        }
        
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                dp[i][j][k] %= mod;
            }
        }
    }
    
    long long answer = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            answer = (answer + dp[n - 1][i][j]) % mod;
        }
    }
    
    long long f = 1;
    for(int i = 1; i <= remaining; i++)
        f = (f * i) % mod;
    printf("%lld\n", (f * answer) % mod);
    
    
    return 0;
}
