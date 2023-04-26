#include <iostream>
#include <vector>

using namespace std;

const long long mod = 998244353;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>>cnt(n, vector<int>(26, 0));
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(char c : s)
            cnt[i][c - 'a']++;
    }
    vector<int>f(1 << n);
    for(int mask = 1; mask < (1 << n); mask++) {
        vector<int>c(26, 1 << 30);
        for(int i = 0; i < n; i++) {
            if(!(mask & (1 << i)))
                continue;
            for(int j = 0; j < 26; j++)
                c[j] = min(c[j], cnt[i][j]);
        }
        f[mask] = (mod - 1 + __builtin_parity(mask) * 2) % mod;
        for(int i = 0; i < 26; i++)
            f[mask] = ((long long)f[mask] * (c[i] + 1)) % mod;
    }
    
    for(int i = 0; i < n; i++)
        for(int mask = 1; mask < (1 << n); mask++)
            f[mask] = (f[mask] + ((mask >> i) & 1) * f[mask ^ (1 << i)]) % mod;
        long long result = 0;
    for(int mask = 1; mask < (1 << n); mask++) {
        long long sum = 0;
        for(int i = 0; i < n; i++)
            sum += ((mask >> i) & 1) * (i + 1);
        result ^= f[mask] * sum * __builtin_popcount(mask);
    }
    cout << result << '\n';
    return 0;
}
