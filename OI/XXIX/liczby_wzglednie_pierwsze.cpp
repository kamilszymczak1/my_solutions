#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void SOS(vector<long long>&dp, int k) { 
    for(int i = 0; i < k; i++) { 
        for(int mask = 0; mask < (1 << k); mask++) {
            if((mask >> i) & 1) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }
}

long long CountCoPrimeNumbers(long long n, long long biggest, vector<pair<long long, int>>&primeFactors) { 
    int k = primeFactors.size();
    vector<long long>dp(1 << k);
    for(int mask = 1; mask < (1 << k); mask++) {
        long long mult = 1;
        for(int i = 0; i < k; i++) {
            if((mask >> i) & 1) {
                mult *= primeFactors[i].first;
            }
        }
        dp[mask] = biggest / mult;
        if(__builtin_popcount(mask) % 2 == 0)
            dp[mask] *= -1;
    }
    SOS(dp, k);
    return biggest - dp[(1 << k) - 1];
}

vector<pair<long long, int>> Factorize(long long n) {
    vector<pair<long long, int>>primeFactors;
    for(long long x = 2; x * x <= n; x++) {
        if(n % x == 0) {
            int cnt = 0;
            while(n % x == 0) {
                n /= x;
                cnt++;
            }
            primeFactors.emplace_back(x, cnt);
        }
    }
    if(n != 1)
        primeFactors.emplace_back(n, 1);
    return primeFactors;
}

int main() {
    ios_base::sync_with_stdio(0);
    long long n, k, c; cin >> n >> k >> c; k--;
    vector<pair<long long, int>>primeFactors = Factorize(n);
    long long fiN = CountCoPrimeNumbers(n, n, primeFactors);
    long long fullCycles = k / fiN;
    k = k % fiN + 1;
    long long beg = 1, end = n;
    while(beg <= end) {
        long long mid = (beg + end) / 2;
        if(CountCoPrimeNumbers(n, mid, primeFactors) < k) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    long long x = n * fullCycles + end + 1;
    cout << x << ' ';
    for(int i = 0; i < c - 1; i++) {
        for(x++; __gcd(x, n) != 1; x++) {}
        cout << x << ' ';
    }
    cout << '\n';
    
    return 0;
}
