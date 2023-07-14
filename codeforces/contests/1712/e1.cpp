#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

long long ceil(long long x, long long y) {
    long long t = x / y;
    if(t * y == x)
        return t;
    return t + 1;
}

long long count(long long l, long long r, long long k) {
    if(l > r)
        return 0;
    return r / k - (l - 1) / k;
}

void test_case() {
    long long l, r; scanf("%lld%lld", &l, &r);
    
    long long len = r - l + 1;
    
    long long all = len * (len - 1) * (len - 2) / 6;
    
    vector<vector<long long>>v(2 * r + 1);
    for(long long i = 1; i <= 2 * r; i++) {
        for(long long j = i + 1; i * j <= 2 * r; j++) {
            if(__gcd(i, j) == 1)
                v[i].push_back(j);
        }
    }
    
    for(long long gcd = 1; gcd <= r * 2; gcd++) {
        for(long long i = ceil(l, gcd); i * gcd <= r * 2; i++) {
            for(long long j : v[i]) {
                if(i * j * gcd > 2 * r)
                    break;
                
                long long lcm = i * gcd * j;
                
                
                all -= count(j * gcd + 1, r, lcm);
                
                if(lcm % 2 == 0) {
                    
                    long long x = j * gcd + 1, y = min(r, gcd * (i + j) - 1);
                    all -= count(x, y, lcm / 2) - count(x, y, lcm);
                }
            }
        }
    }
    
    
    printf("%lld\n", all);
    
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

