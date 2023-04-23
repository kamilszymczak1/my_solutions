#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const long long mod = 1'000'000'007;

long long lcm(long long a, long long b) {
    return a * b / __gcd(a, b);
}

bool Contains(long long a, long long p, long long x, long long v) {
    if(v - a < 0 || (v - a) % p != 0)
        return false;
    return (v - a) / p < x;
}

void TestCase() {
    long long b, q, y; scanf("%lld%lld%lld", &b, &q, &y);
    long long c, r, z; scanf("%lld%lld%lld", &c, &r, &z);
    
    if(r % q != 0) {
        printf("0\n");
        return;
    }
    
    if(Contains(b, q, y, c) == false) {
        printf("0\n");
        return;
    }
    
    if(Contains(b, q, y, c + r * (z - 1)) == false) {
        printf("0\n");
        return;
    }
    
    long long prevC = c - r, nextC = c + r * z;
    
    if(Contains(b, q, y, prevC) == false || Contains(b, q, y, nextC) == false) {
        printf("-1\n");
        return;
    }
    
    long long answer = 0;
    for(long long div = 1; div * div <= r; div++) {
        if(r % div == 0) {
            if(lcm(q, div) == r) {
                answer += (r / div) * (r / div);
                answer %= mod;
            }
            
            if(div != r / div && lcm(q, r / div) == r) {
                answer += div * div;
                answer %= mod;
            }
        }
    }
    
    printf("%lld\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
