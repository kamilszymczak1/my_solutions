#include <iostream>

using namespace std;

const long long mod = 1e9 + 7;

long long ModPow(int x, int exp) {
    if(exp <= 0)
        return 1;
    long long result = ModPow(x, exp / 2);
    result = (result * result) % mod;
    if(exp & 1)
        result = (result * x) % mod;
    return result;
}

void TestCase() {
    int n, k; cin >> n >> k;
    long long result = 1, binomSum = 0, binom = 1;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0)
            binomSum = (binomSum + binom) % mod;
        binom = (((binom * (n - i)) % mod) * ModPow(i + 1, mod - 2)) % mod;
    }
    for(int i = 0; i < k; i++) {
        long long newResult = (n & 1) ? result : ModPow(ModPow(2, i), n);
        result = (newResult + binomSum * result) % mod;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
