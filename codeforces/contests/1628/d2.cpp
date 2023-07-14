#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long mod = 1000000007;

long long ModPow(int x, long long exp) {
    if(exp == 0)
        return 1;
    long long result = ModPow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

void TestCase() {
    int n, m, k; cin >> n >> m >> k;
    if(n == 1) {
        cout << (m == 1 ? k : 0) << '\n';
        return;
    }
    vector<long long>factorial(n + 1, 1), invFactorial(n + 1, 1), inv(n + 1, 1);
    for(int i = 2; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % mod;
        inv[i] = (mod - (mod / i) * inv[mod % i] % mod) % mod;
        invFactorial[i] = invFactorial[i - 1] * inv[i] % mod;
    }
    
    auto Choose = [&factorial, &invFactorial] (int x, int y) -> long long {
        long long bottom = invFactorial[y] * invFactorial[x - y] % mod;
        return factorial[x] * bottom % mod;
    };
    
    long long result = 0, pow2i = 1;
    for(int i = 1; i <= m; i++) {
        long long contribution = Choose(n - i - 1, m - i);
        long long value = i * pow2i % mod;
        result = (result + contribution * value) % mod;
        pow2i = pow2i * 2 % mod;
    }
    if(n == m)
        result = n * ModPow(2, n - 1) % mod;
    result = result * k % mod * ModPow(ModPow(2, mod - 2), n - 1) % mod;
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
