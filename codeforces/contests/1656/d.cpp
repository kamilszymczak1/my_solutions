#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long LEQ(long long x, long long y) {
    long double t = x;
    t = t * (t + 1) / 2;
    if(t > y)
        return false;
    return x * (x + 1) / 2 <= y;
}

void TestCase() {
    long long n; scanf("%lld", &n);
    if(n % 2 == 1) {
        printf("2\n");
        return;
    }
    
    long long t = 1, x = n;
    while(x % 2 == 0) {
        x /= 2;
        t *= 2;
    }
    
    if(x == 1) {
        printf("-1\n");
        return;
    }
    
    if(LEQ(t * 2, n)) {
        printf("%lld\n", t * 2);
        return;
    }
    
    if(LEQ(x, n)) {
        printf("%lld\n", x);
        return;
    }
    
    printf("-1\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
