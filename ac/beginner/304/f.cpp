#include <iostream>
#include <vector>

using namespace std;

const int mod = 998244353;

int mod_pow(int x, int exp) {
    if(exp == 0)
        return 1;
    int result = mod_pow(x, exp / 2);
    result = 1ll * result * result % mod;
    if(exp & 1)
        result = 1ll * x * result % mod;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    
    string s; cin >> s;
    
    vector<int>cnt(n);
    
    int result = 0;
    
    for(int i = 1; i < n; i++) {
        if(n % i == 0) {
            int count = 0;
            for(int j = 0; j < i; j++) {
                bool all_togled = true;
                for(int k = j; k < n; k += i) {
                    if(s[k] == '.') {
                        all_togled = false;
                    }
                }
                count += all_togled;
            }
            
            cnt[i] = mod_pow(2, count);
            
            for(int j = 1; j < i; j++) {
                if(i % j == 0) {
                    cnt[i] -= cnt[j];
                    if(cnt[i] < 0)
                        cnt[i] += mod;
                }
            }
            
            result += cnt[i];
            if(result >= mod)
                result -= mod;
        }
    }
    
    cout << result << '\n';
    
    return 0;
}
