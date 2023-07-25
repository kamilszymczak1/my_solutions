#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        long long a, b, c, d; scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        long long g1 = __gcd(a, b);
        long long g2 = __gcd(c, d);
        a /= g1; b /= g1;
        c /= g2; d /= g2;
        
        if(a * d == c * b) {
            printf("0\n");
        } else {
            if((c != 0 && (a * d) % (c * b) == 0) || (a != 0 && (c * b) % (a * d) == 0)) {
                printf("1\n");
            } else {
                printf("2\n");
            }
        }
    }
}
