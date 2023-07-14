#include <iostream>
#include <algorithm>

using namespace std;

const int mod = 998'244'353;

const int MAX_N = 507;

int add(int x, int y) { return (x + y) >= mod ? (x + y - mod) : (x + y); }
int mult(int x, int y) { return 1ll * x * y % mod; }

int mod_pow(int x, int exp) {
    int answer = 1;
    for(int i = 0; (1 << i) <= exp; i++) {
        if(exp & (1 << i))
            answer = mult(answer, x);
        x = mult(x, x);
    }
    return answer;
}

int get_inv(int x) { return mod_pow(x, mod - 2); }

int n, k;
int choose[4 * MAX_N][4 * MAX_N];

int dp[3 * MAX_N][MAX_N][4], inv[MAX_N * 4];

int f(int l) {
    int answer = 0;
    
    for(int i = 0; 4 * i <= l; i++) {
        int ways = 1;
        ways = mult(ways, choose[l][i]);
        ways = mult(ways, choose[4 * n - l - 1][n - 1 - i]);
        ways = mult(ways, dp[l - i][i + 1][0]);
        answer = add(answer, ways);
    }
    
    for(int j = 1; j <= 3; j++) {
        for(int i = 0; 4 * i <= l; i++) {
            int ways = 1;
            ways = mult(ways, choose[l][i]);
            ways = mult(ways, choose[4 * n - l - 1][n - 1 - i]);
            ways = mult(ways, dp[l - i][i][j]);
            ways = mult(ways, inv[j + 1]);
            answer = add(answer, ways);
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    
    for(int i = 0; i <= 4 * n; i++)
        inv[i] = get_inv(i);
    
    for(int i = 0; i <= 4 * n; i++) {
        choose[i][0] = choose[i][i] = 1;
        for(int j = 1; j < i; j++)
            choose[i][j] = add(choose[i - 1][j], choose[i - 1][j - 1]);
    }
    
    for(int a = 0; a <= n; a++) {
        for(int b = 0; b <= n; b++) {
            for(int c = 0; c <= n; c++) {
                
                int lo = min({a, b, c});
                int lo_count = (int)(a == lo) + (int)(b == lo) + (int)(c == lo);
                
                int ways = 1;
                ways = mult(ways, choose[a + b + c][a]);
                ways = mult(ways, choose[b + c][b]);
                
                ways = mult(ways, choose[3 * n - a - b - c][n - a]);
                ways = mult(ways, choose[2 * n - b - c][n - b]);
                
                dp[a + b + c][lo][lo_count] = add(dp[a + b + c][lo][lo_count], ways);
                dp[a + b + c][lo][0] = add(dp[a + b + c][lo][0], ways);
            }
        }
    }
    
    for(int i = 0; i <= 3 * n; i++) {
        for(int j = n - 1; j >= 0; j--) {
            dp[i][j][0] = add(dp[i][j][0], dp[i][j + 1][0]);
        }
    }
    
    int answer = 0;
    for(int i = 2; i <= 4 * n; i++) {
        answer = add(answer, f(min(i - 1, k)));
    }
    
    answer = mult(answer, 4);
    
    int div = 1;
    div = mult(div, choose[4 * n][n]);
    div = mult(div, choose[3 * n][n]);
    div = mult(div, choose[2 * n][n]);
    
    
    answer = mult(answer, get_inv(div));
    
    answer = add(answer, inv[4]);
    
    cout << answer << '\n';
    
    return 0;
}
