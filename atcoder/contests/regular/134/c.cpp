#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 998244353;

long long ModPow(int x, long long exp) {
    if(exp == 0)
        return 1;
    long long result = ModPow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    
    vector<long long>factorial(n + k + 1, 1);
    for(int i = 2; i <= n + k; i++)
        factorial[i] = (factorial[i - 1] * i) % mod;
    
    auto Choose = [&factorial] (long long x, long long y) -> long long {
        long long result = 1;
        for(int i = x; i > y; i--)
            result = (result * i) % mod;
        return result * ModPow(factorial[x - y], mod - 2) % mod;
    };
    
    vector<long long>a(n);
    long long sum = 0, result = 1;
    cin >> a[0];
    for(int i = 1; i < n; i++) {
        cin >> a[i];
        result = result * Choose(a[i] + k - 1, a[i]) % mod;
        sum += a[i];
    }
    
    if(a[0] - sum >= k) {
        a[0] -= sum + k;
        result = result * Choose(a[0] + k - 1, a[0]) % mod;
    } else {
        result *= 0;
    }
    
    cout << result << '\n';
    
    return 0;
}
