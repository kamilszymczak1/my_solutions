#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

const long long mod = 998244353;
char c[1001], s[20];

void SOS(vector<int>&dp, int p) {
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < (1 << p); j++) {
            if((j >> i) & 1) {
                dp[j] += dp[j ^ (1 << i)];
                if(dp[j] >= mod)
                    dp[j] -= mod;
            }
        }
    }
}

void Calc(vector<pair<int, int>>&queries, int p, vector<int>&ans, int n) {
    
    vector<int>dp(1 << 17), Pow(n + 1, 1);
    for(int i = 1; i <= n; i++)
        Pow[i] = (1ll * Pow[i - 1] * p) % mod;
    
    int marks = 0;
    for(int i = 0; i < n; i++)
        marks += c[i] == '?';
    
    for(int i = 0; i < n - 1; i++) {
        int mask = 0, free = 0, local = 0;
        for(int k = 0; i - k >= 0 && i + 1 + k < n; k++) {
            int a = i - k, b = i + 1 + k;
            local += c[a] == '?';
            local += c[b] == '?';
            
            if(c[a] == c[b]) {
                free += c[a] == '?';
            } else {
                if(c[a] == '?') {
                    mask |= 1 << (c[b] - 'a');
                } else if(c[b] == '?') {
                    mask |= 1 << (c[a] - 'a');
                } else {
                    break;
                }
            }
            
            dp[mask] += Pow[free + marks - local];
            if(dp[mask] >= mod)
                dp[mask] -= mod;
        }
    }
    
    for(int i = 0; i < n; i++) {
        int mask = 0, free = 0, local = 0;
        for(int k = 0; i - k >= 0 && i + k < n; k++) {
            int a = i - k, b = i + k;
            
            local += c[a] == '?';
            if(a != b)
                local += c[b] == '?';
            
            if(c[a] == c[b]) {
                free += c[a] == '?';
            } else {
                if(c[a] == '?') {
                    mask |= 1 << (c[b] - 'a');
                } else if(c[b] == '?') {
                    mask |= 1 << (c[a] - 'a');
                } else {
                    break;
                }
            }
            
            dp[mask] += Pow[free + marks - local];
            if(dp[mask] >= mod)
                dp[mask] -= mod;
        }
    }
    
    SOS(dp, 17);
    
    for(auto [mask, id] : queries) {
        ans[id] += dp[mask];
        if(ans[id] >= mod)
            ans[id] -= mod;
    }
}

void TestCase() {
    int n, q; scanf("%d%s%d", &n, c, &q);
    vector<vector<pair<int, int>>>queries(18);
    for(int i = 0; i < q; i++) {
        scanf("%s", s);
        int mask = 0, t = strlen(s);
        for(int j = 0; j < t; j++)
            mask |= 1 << (s[j] - 'a');
        queries[t].emplace_back(mask, i);
    }
    
    vector<int>ans(q);
    for(int i = 1; i <= 17; i++) {
        Calc(queries[i], i, ans, n);
    }
    
    for(int x : ans)
        printf("%d\n", x);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
