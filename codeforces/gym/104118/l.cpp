#include <iostream>
#include <cmath>
#include <unordered_map>
    
using namespace std;
    
long long mod_pow(long long a, long long exp, long long p) {
    if(exp == 0)
        return 1;
    long long result = mod_pow(a, exp >> 1, p);
    result = result * result % p;
    if(exp & 1)
        result = a * result % p;
    return result;
}
    
long long discrete_logarithm(long long a, long long b, long long p) {
    long long k = ceil(sqrt(p)) + 1;
    
    unordered_map<long long, long long>m;
    
    long long my_pow_inv = 1, my_pow = 1;
    long long inv_a = mod_pow(a, p - 2, p);
    
    for(int i = 0; i < k; i++) {
        
        long long t = my_pow_inv * b % p;
        
        if(m.find(t) == m.end()) {
            m[t] = i;
        }
        
        my_pow_inv = my_pow_inv * inv_a % p;
        my_pow = my_pow * a % p;
    }
    
    long long answer = p;
    
    long long my_pow_pow = 1;
    for(int i = 0; i <= k + 7; i++) {
    
        if(m.find(my_pow_pow) != m.end()) {
            answer = min(answer, i * k + m[my_pow_pow]);
        }
        
        my_pow_pow = my_pow_pow * my_pow % p;
    }
    
    return answer == p ? -1 : answer;
}
    
    
    
void test_case() {
    long long a, b, s, p, v;
    cin >> a >> b >> s >> p >> v;
    
    if(s == v) {
        cout << "0\n";
        return;
    }
    
    if((a * s + b) % p == s) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    
    long long n = p;
    
    if(a != 1) {
        long long numerator = (v * (a - 1) + b) % p;
        
        long long denominator = (s * (a - 1) + b) % p;
        
        long long c = numerator * mod_pow(denominator, p - 2, p) % p;
        
        n = discrete_logarithm(a, c, p);
    } else {
        n = (v - s + p) * mod_pow(b, p - 2, p) % p;
    }
    
    if(n == -1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    
    cout << n << '\n';
}
    
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
