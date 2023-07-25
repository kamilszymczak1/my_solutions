#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const long long mod = 1'000'000'007;

long long PowMod(long long x, long long exp) {
    long long result = 1, xPow = x;
    for(; exp; exp >>= 1) {
        if(exp & 1)
            result = (result * xPow) % mod;
        xPow = (xPow * xPow) % mod;
    }
    return result;
}

long long Sq(long long x) {
    return (x * x) % mod;
}

long long Inv(long long x) {
    return PowMod(x, mod - 2);
}

void TestCase() {
    int n, m; cin >> n >> m;
    int S = (2 * n - 2) * (2 * m - 2);
    int rb, cb; cin >> rb >> cb;
    int rd, cd; cin >> rd >> cd;
    long long prevInte = 0;
    long long p; cin >> p;
    long long q = ((100 - p) * Inv(100)) % mod;
    p = (p * Inv(100)) % mod;
    long long EV1 = 0, step = 0, qPow = 1;
    int dx = rb == 1 ? -1 : 1, dy = cb == 1 ? -1 : 1;
    for(long long t = 0; t < S; t++) {
        if(rb == n || rb == 1)
            dx *= -1;
        if(cb == m || cb == 1)
            dy *= -1;
        if(rb == rd || cb == cd) {
            EV1 = (EV1 + t * qPow) % mod;
            step = (step + S * qPow) % mod;
            qPow = (qPow * q) % mod;
        }
        rb += dx; cb += dy;
    }
    
    long long A = (step * qPow) % mod;
    long long B = Sq((1 - qPow + mod) % mod);
    long long C = (EV1 * Inv((1 - qPow + mod) % mod)) % mod;
    long long result = (p * (((A * Inv(B)) % mod) + C)) % mod;
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
