#include <cstdio>
#include <cmath>

using namespace std;

long long query(int a, int b) {
    printf("? %d %d\n", a, b);
    fflush(stdout);
    long long x; scanf("%lld", &x);
    return x;
}

void test_case() {
    int n; scanf("%d", &n);
    
    long long total = query(1, n);
    
    long long l = n;
    for(int i = 29; i >= 0; i--) {
        l -= 1 << i;
        if(l <= 0 || query(l, n) != 0)
            l += 1 << i;
    }
    
    long long len2 = query(1, l) - query(1, l - 1) + 1;
    
    total -= len2 * (len2 - 1) / 2;
    
    long long len1 = (1 + round(sqrt(1 + 8 * total))) / 2;
    
    printf("! %lld %lld %lld\n", l - len2 - len1 + 1, l - len2 + 1, l);
    fflush(stdout);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
