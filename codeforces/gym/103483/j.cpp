#include <iostream>
#include <vector>
#include <cassert>
    
using namespace std;
    
const int mod = 998'244'353;
    
int mod_pow(int x, int exp) {
    int result = 1;
    for(int i = 0; (1 << i) <= exp; i++) {
        if(exp & (1 << i))
            result = 1ll * result * x % mod;
        x = 1ll * x * x % mod;
    }
    return result;
}
    
int choose(int n, int k, vector<int>&fact) {
    int answer = fact[n];
    answer = 1ll * answer * mod_pow(fact[k], mod - 2) % mod;
    answer = 1ll * answer * mod_pow(fact[n - k], mod - 2) % mod;
    return answer;
}
    
int main() {
    int n, m; cin >> n >> m;
    vector<int>fact(n + m + 1);
    fact[0] = 1;
    for(int i = 1; i <= n + m; i++)
        fact[i] = 1ll * fact[i - 1] * i % mod;
    
    if(n == 1 || m == 1) {
        cout << "1\n";
        return 0;
    }
    
    int x = choose(n + m - 2, m - 1, fact);
    x = 1ll * x * x % mod;
    
    int y = 1ll * choose(n + m - 2, m, fact) * choose(n + m - 2, n, fact) % mod;
    
    int answer = (x - y + mod) % mod;
    
    cout << answer << '\n';
    
    return 0;
}
