#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr long long mod = 998244353;

long long pow(long long x, long long exp) {
    if(exp == 0)
        return 1;
    long long result = pow(x, exp >> 1);
    result = (result * result) % mod;
    if(exp & 1)
        result = (result * x) % mod;
    return result;
}

long long Calc(vector<long long>&v, int n) {
    for(auto &x : v)
        x--;
    sort(v.begin(), v.end());
    long long result = 1;
    for(int i = 0; i < n; i++) {
        result = (result * (v[i] - i)) % mod;
    }
    return result;
}

long long Factorial(long long x) {
    long long result = 1;
    for(long long i = 2; i <= x; i++)
        result = (result * i) % mod;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    long long n, m; cin >> n >> m;
    vector<vector<int>>v(n, vector<int>(m));
    for(auto &x : v) {
        for(auto &y : x) {
            cin >> y;
        }
    }
    
    long long sum = (Factorial(n) * m) % mod;
    for(int i = 0; i < m; i++) {
        vector<long long>p;
        for(int j = 0; j < n; j++)
            p.push_back(v[j][i]);
        sum = (sum - Calc(p, n) + mod) % mod;
    }
    
    cout << (sum * pow(Factorial(n), mod - 2)) % mod << '\n';
    
    
    return 0;
}
