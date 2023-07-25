#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

long long Ceil(long long x, long long y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

long long Query(long long x) {
    printf("? %lld\n", x);
    fflush(stdout);
    long long ret; scanf("%lld", &ret);
    return ret;
}

void TestCase() {
    long long n; scanf("%lld", &n);
    long long L = 0;
    for(int i = 21; i >= 0; i--) {
        L += 1 << i;
        if(Query(L) == 1)
            L -= 1 << i;
    }
    L -= n - 2;
    long long result = L + n - 1;
    for(int h = 2; h <= n; h++) {
        long long w = Ceil(L + n - h, h);
        if(w > 0) {
            long long h = Query(w);
            if(h != 0)
                result = min(result, h * w);
        }
    }
    printf("! %lld\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
