#include <bits/stdc++.h>
using namespace std;
    
const int MAX_N = 4007;
    
const long long inf = 1ll << 60;
    
int n;
long long t[MAX_N][2];
long long pref[MAX_N][2];
long long prog_nor[MAX_N][2];
long long prog_rev[MAX_N][2];
    
long long dp[MAX_N][2];
    
long long cost(int l, int r, int i) {
    if(l == 1) {
        return prog_rev[r][i] - (n - r) * pref[r][i];
    }
    
    if(r == n) {
        return prog_nor[n][i] - prog_nor[l - 1][i] - (l - 1) * (pref[n][i] - pref[l - 1][i]);
    }
    
    if(l == r)
        return t[l][i];
    
    int m = (l + r) / 2;
    
    
    //[l, m], [m + 1, r]
    
    long long L = prog_nor[m][i] - prog_nor[l - 1][i] - (l - 1) * (pref[m][i] - pref[l - 1][i]);
    
    long long R = prog_rev[r][i] - prog_rev[m][i] - (n - r) * (pref[r][i] - pref[m][i]);
    
    return L + R;
    
}
    
long long test() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 2; j++) {
            cin >> t[i][j];
            pref[i][j] = pref[i - 1][j] + t[i][j];
            prog_nor[i][j] = prog_nor[i - 1][j] + t[i][j] * i;
            prog_rev[i][j] = prog_rev[i - 1][j] + t[i][j] * (n + 1 - i);
        }
    }
    
    for(int i = 0; i <= n; i++) {
        dp[i][0] = dp[i][1] = inf;
    }
    dp[0][0] = dp[0][1] = 0;
    
    
    for(int i = 1; i < n; i++) {
        dp[i][0] = cost(1, i, 0);
        dp[i][1] = cost(1, i, 1);
    }
    
    for(int i = 2; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            for(int k = 0; k < 2; k++) {
                dp[j][k] = min(dp[j][k], dp[i - 1][k ^ 1] + cost(i, j, k));
            }
        }
    }
    
    
    return min(dp[n][0], dp[n][1]);
}
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i=1; i<=t; ++i) {
        auto wynik = test();
        cout<<"Case #"<<i<<": "<<wynik<<'\n';
    }
}
