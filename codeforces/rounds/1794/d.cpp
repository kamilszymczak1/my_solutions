#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_A = 1'000'007;

const long long mod = 998244353;

long long mod_pow(long long a, long long exp) {
    if(exp == 0)
        return 1;
    long long result = mod_pow(a, exp >> 1);
    result = result * result % mod;
    if(exp & 1)
        result = result * a % mod;
    return result;
}

bool prime[MAX_A];
long long factorial[MAX_A], inv_factorial[MAX_A];

long long choose(int n, int k) {
    long long result = factorial[n];
    result = result * inv_factorial[k] % mod;
    result = result * inv_factorial[n - k] % mod;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    fill(prime + 2, prime + MAX_A, true);
    for(int i = 2; i < MAX_A; i++) {
        if(prime[i]) {
            for(int j = i + i; j < MAX_A; j += i) {
                prime[j] = false;
            }
        }
    }
    
    factorial[0] = 1;
    for(int i = 1; i < MAX_A; i++)
        factorial[i] = factorial[i - 1] * i % mod;
    inv_factorial[MAX_A - 1] = mod_pow(factorial[MAX_A - 1], mod - 2);
    for(int i = MAX_A - 2; i >= 0; i--)
        inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % mod;
    
    vector<int>primes, exponents;
    
    int n; cin >> n;
    for(int i = 0; i < 2 * n; i++) {
        int x; cin >> x;
        if(prime[x]) {
            primes.push_back(x);
        } else {
            exponents.push_back(x);
        }
    }
    
    sort(primes.begin(), primes.end());
    sort(exponents.begin(), exponents.end());
    
    
    if(primes.size() < n) {
        cout << "0\n";
        return 0;
    }
    
    long long exp_factor = 1;
    
    int indices = n;
    for(int i = 0; i < (int)exponents.size(); i++) {
        int j = i;
        while(j < (int)exponents.size() && exponents[i] == exponents[j])
            j++;
        exp_factor = exp_factor * choose(indices, j - i) % mod;
        indices -= j - i;
        i = j - 1;
    }
    
    vector<long long>dp(indices + 1);
    dp[0] = 1;
    
    for(int i = 0; i < (int)primes.size(); i++) {
        int j = i;
        while(j < (int)primes.size() && primes[i] == primes[j])
            j++;
        
        vector<long long>new_dp(indices + 1);
        
        for(int new_fact = 0; new_fact <= 1; new_fact++) {
            int new_exp = j - i - new_fact;
            
            for(int to_exp = 0; to_exp <= min(i, indices) && to_exp + new_exp <= indices; to_exp++) {
                int to_fact = i - to_exp;
                
                new_dp[to_exp + new_exp] += dp[to_exp] * choose(indices - to_exp, new_exp) % mod;
                new_dp[to_exp + new_exp] %= mod;
                
            }
            
        }
        
        swap(dp, new_dp);
        
        i = j - 1;
    }
    
    cout << exp_factor * dp[indices] % mod << '\n';
    
    
    return 0;
}
