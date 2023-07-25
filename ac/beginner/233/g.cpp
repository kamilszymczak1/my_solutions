#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int MAX_N = 51, inf = 100;

int dp[MAX_N][MAX_N][MAX_N][MAX_N], verticalPref[MAX_N][MAX_N], horizontalPref[MAX_N][MAX_N];
char c[MAX_N][MAX_N];

int Calc(int i, int j, int k, int l) {
    if(i > k || j > l)
        return 0;
    if(dp[i][j][k][l] != inf)
        return dp[i][j][k][l];
    dp[i][j][k][l] = max(k - i + 1, l - j + 1);
    for(int split = i; split <= k; split++) {
        if(horizontalPref[split][l] - horizontalPref[split][j - 1] == 0) {
            dp[i][j][k][l] = min(dp[i][j][k][l], Calc(i, j, split - 1, l) + Calc(split + 1, j, k, l));
        }
    }
    for(int split = j; split <= l; split++) {
        if(verticalPref[k][split] - verticalPref[i - 1][split] == 0) {
            dp[i][j][k][l] = min(dp[i][j][k][l], Calc(i, j, k, split - 1) + Calc(i, split + 1, k, l));
        }
    }
    return dp[i][j][k][l];
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = i; k <= n; k++) {
                for(int l = j; l <= n; l++) {
                    dp[i][j][k][l] = inf;
                }
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> c[i][j];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            verticalPref[i][j] = verticalPref[i - 1][j] + (c[i][j] == '#');
            horizontalPref[i][j] = horizontalPref[i][j - 1] + (c[i][j] == '#');
        }
    }
    
    cout << Calc(1, 1, n, n) << '\n';
    
    return 0;
}
