#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

const long long inf = 1ll << 50;

void test_case() {
    int n; scanf("%d", &n);
    long long x; scanf("%lld", &x);
    long long lo = -inf, hi = inf;
    int result = 0;
    for(int i = 0; i < n; i++) {
        long long a; scanf("%lld", &a);
        long long myLo = a - x, myHi = a + x;
        if(myHi < lo || myLo > hi) {
            lo = myLo;
            hi = myHi;
            result++;
        } else {
            hi = min(myHi, hi);
            lo = max(lo, myLo);
        }
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
