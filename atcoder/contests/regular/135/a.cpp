#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


const long long mod = 998244353;

map<long long, long long>m;

long long Calc(long long x) {
    if(x <= 3)
        return x;
    if(m[x] != 0)
        return m[x];
    if(x % 2 == 0) {
        long long result = Calc(x / 2);
        result = (result * result) % mod;
        return m[x] = result;
    }
    long long result = Calc(x / 2);
    result = (result * Calc(x / 2 + 1)) % mod;
    return m[x] = result;
}

int main() {
    ios_base::sync_with_stdio(0);
    long long n; cin >> n;
    cout << Calc(n) << '\n';
    
    return 0;
}
