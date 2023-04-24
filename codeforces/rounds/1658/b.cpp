#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const long long mod = 998244353;

void TestCase() {
    int n; scanf("%d", &n);
    if(n % 2 == 1) {
        printf("0\n");
        return;
    }
    
    long long f = 1;
    for(int i = 1; i <= n / 2; i++)
        f = (f * i) % mod;
    printf("%lld\n", (f * f) % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
