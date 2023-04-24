#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

const long long MAX_N = 500'000;

const long long mod = 1'000'000'007;

long long mod_pow(long long x, int exp) {
    if(exp == 0)
        return 1;
    long long result = mod_pow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

long long factorial[MAX_N], inv_factorial[MAX_N];

long long choose(int n, int k) {
    if(k < 0 || k > n)
        return 0;
    long long t = factorial[n];
    t = t * inv_factorial[k] % mod;
    t = t * inv_factorial[n - k] % mod;
    return t;
}

int main() {
    factorial[0] = 1;
    for(int i = 1; i < MAX_N; i++)
        factorial[i] = factorial[i - 1] * i % mod;
    inv_factorial[MAX_N - 1] = mod_pow(factorial[MAX_N - 1], mod - 2);
    for(int i = MAX_N - 2; i >= 0; i--)
        inv_factorial[i] = inv_factorial[i + 1] * (i + 1) % mod;
    
    int n; scanf("%d", &n);
    n++;
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    long long result = 0;
    for(int i = 0; i < n; i++) {
        result += choose(i + a[i], a[i] - 1);
        result %= mod;
    }
    
    printf("%lld\n", result);
    
    return 0;
}
