#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const long long mod = 998244353;

long long FastPow(long long x, int exp) {
    if(exp == 0)
        return 1;
    long long result = FastPow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

long long Inv(long long x) {
    return FastPow(x, mod - 2);
}

long long Fac(long long n, long long k) {
    if(k > n || k < 0)
        return 0;
    long long result = 1;
    for(int i = 0; i < k; i++)
        result = (result * (n - i)) % mod;
    for(int i = 1; i <= k; i++)
        result = (result * Inv(i)) % mod;
    return result;
}

void TestCase() {
    long long n, k, x; scanf("%lld%lld%lld", &n, &k, &x);
    
    if(n * (n - 1) / 2 < k || x > n - 1 || k < x) {
        printf("0\n");
        return;
    }
    
    long long result = 0;
    if(k == x) {
        //first case is that we don't choose anything on the borders
        result += 
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
