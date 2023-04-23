#include <cstdio>

using namespace std;

const long long mod = 1'000'000'007;

const long long mod_pow(long long x, long long exp) {
    if(exp == 0)
        return 1;
    long long result = mod_pow(x, exp / 2);
    result = (result * result) % mod;
    if(exp % 2 == 1)
        result = (result * x) % mod;
    return result;
}

void test_case() {
    int n, k; scanf("%d%d", &n, &k);
    if(k >= n) {
        printf("%lld\n", mod_pow(2, n));
        return;
    } else {
        long long choose = 1;
        long long answer = 0;
        for(int i = 0; i <= k; i++) {
            answer = (answer + choose) % mod;
            long long to_mult = mod_pow(i + 1, mod - 2) * (n - i) % mod;
            choose = (choose * to_mult) % mod;
        }
        printf("%lld\n", answer);
    }
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
