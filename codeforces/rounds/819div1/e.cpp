#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>
#include <cassert>

using namespace std;

const long long mod = 998244353;

long long mod_pow(long long x, long long exp) {
    long long result = 1;
    for(; exp > 0; exp >>= 1) {
        if(exp & 1) {
            result = result * x % mod;
        }
        x = x * x % mod;
    }
    return result;
}

void test_case() {
    int n; scanf("%d", &n);
    
    vector<long long>p(n + 1, 1);
    for(int i = 2; i <= n; i++)
        p[i] = (p[i - 1] + p[i - 2] * (i - 1)) % mod;
    
    vector<long long>fact(n + 1, 1), inv_fact(n + 1, 1);
    for(int i = 2; i <= n; i++)
        fact[i] = fact[i - 1] * i % mod;
    inv_fact[n] = mod_pow(fact[n], mod - 2);
    for(int i = n - 1; i >= 0; i--)
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
    
    long long pow2i = 1, f = 1, answer = 0;
    
    for(int i = 0; i * 4 <= n; i++) {
        
        
        
        long long choose = 1;
        choose = choose * fact[n - 2 * i] % mod;
        choose = choose * inv_fact[2 * i] % mod;
        choose = choose * inv_fact[n - 4 * i] % mod;
        
        long long c = 1;
        c = c * choose % mod;
        c = c * f % mod;
        c = c * p[n - 4 * i] % mod;
        c = c * pow2i % mod;
        answer += c;
        
        f = f * (2 * i + 1) % mod;
        pow2i = (pow2i << 1) >= mod ? (pow2i << 1) - mod : (pow2i << 1);
    }
    
    
    printf("%lld\n", answer % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
