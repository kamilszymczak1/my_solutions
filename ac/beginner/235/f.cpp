    #include <algorithm>
    #include <iostream>
    #include <vector>
        
    using namespace std;
        
    const long long mod = 998244353;
     
    void Add(int &a, int b) {
        a += b;
        if(a >= mod)
            a -= mod;
    }
        
        
    int main() {
        ios_base::sync_with_stdio(0);
        string s; cin >> s;
        int n = s.size(), M = 10, m, requiredDigits = 0, sMask = 0, sSum = 0; cin >> m;
        for(int i = 0; i < m; i++) {
            int x; cin >> x;
            requiredDigits ^= (1 << x);
        }
        
        vector<vector<int>>sum(2, vector<int>(1 << 10, 0)), cnt(2, vector<int>(1 << 10, 0));
        vector<int>pow10(n, 1);
        for(int i = n - 2; i >= 0; i--)
            pow10[i] = (1ll * pow10[i + 1] * 10) % mod;
        
        for(int digit = 1; digit < s[0] - '0'; digit++) {
            cnt[0][1 << digit] = 1;
            sum[0][1 << digit] = (1ll * digit * pow10[0]) % mod;
        }
        sMask = 1 << (s[0] - '0');
        sSum = (1ll * (s[0] - '0') * pow10[0]) % mod;
        
        for(int i = 1; i < n; i++) {
            for(int mask = 0; mask < (1 << M); mask++) {
                sum[1][mask] = cnt[1][mask] = 0;
            }
            
            for(int digit = 1; digit < 10; digit++) {
                Add(cnt[1][1 << digit], 1);
                sum[1][1 << digit] = (sum[1][1 << digit] + 1ll * digit * pow10[i]) % mod;
            }
            
            
            for(int mask = 2; mask < (1 << M); mask++) {
                for(int digit = 0; digit < 10; digit++) {
                    int newMask = mask | (1 << digit);
                    long long digitValue = (1ll * pow10[i] * digit) % mod;
                    Add(cnt[1][newMask], cnt[0][mask]);
                    sum[1][newMask] = (sum[1][newMask] + sum[0][mask] + cnt[0][mask] * digitValue) % mod;
                }
            }
            
            for(int digit = 0; digit < s[i] - '0'; digit++) {
                int newMask = sMask | (1 << digit);
                Add(cnt[1][newMask], 1);
                sum[1][newMask] = (sum[1][newMask] + sSum + 1ll * pow10[i] * digit) % mod;
            }
            
            sMask |= 1 << (s[i] - '0');
            sSum = (sSum + 1ll * (s[i] - '0') * pow10[i]) % mod;
            swap(sum[0], sum[1]);
            swap(cnt[0], cnt[1]);
        }
        
        int result = sSum * ((sMask & requiredDigits) == requiredDigits);
        for(int i = 0; i < (1 << M); i++)
            Add(result, sum[0][i] * ((i & requiredDigits) == requiredDigits));
        
        cout << result << '\n';
        return 0;
    }
