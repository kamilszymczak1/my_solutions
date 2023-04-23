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
    //count integers divisible by k on range [l, r]
    return r / k - (l - 1) / k;
}

int main() {
    
    const long long MAX_K = 5;
    vector<long long>s(MAX_K + 1), f(MAX_K + 1);
    
    vector<vector<long long>>v(MAX_K * 2 + 1);
    for(long long i = 1; i <= MAX_K * 2; i++) {
        for(long long j = i + 1; j * i <= MAX_K * 2; j++) {
            if(__gcd(i, j) == 1) {
                v[i].push_back(j);
            }
        }
    }
    
    for(long long gcd = 1; gcd <= 2 * MAX_K; gcd++) {
        for(long long i = 1; i * gcd <= 2 * MAX_K; i++) {
            for(long long j : v[i]) {
                if(i * j * gcd > 2 * MAX_K)
                    break;
                
                long long lcm = i * gcd * j;
                long long k = 1;
                while(k * lcm <= j * gcd)
                    k++;
                for(; k * lcm <= MAX_K; k++) {
                    printf("triple %lld %lld %lld\n", i * gcd, j * gcd, k * lcm);
                    s[i * gcd]++;
                    f[k * lcm]++;
                }
                
                if(lcm % 2 == 0) {
                    k = 1;
                    while(k * lcm <= j * gcd)
                        k++;
                    for(; k * lcm <= min(MAX_K, gcd * (i + j) - 1); k++) {
                        printf("sub triple %lld %lld %lld\n", i * gcd, j * gcd, k * lcm);
                        s[i * gcd]--;
                        f[k * lcm]--;
                    }
                    
                    lcm /= 2;
                    k = 1;
                    while(k * lcm <= j * gcd)
                        k++;
                    for(; k * lcm <= min(MAX_K, gcd * (i + j) - 1); k++) {
                        printf("triple %lld %lld %lld\n", i * gcd, j * gcd, k * lcm);
                        s[i * gcd]++;
                        f[k * lcm]++;
                    }
                }
            }
        }
    }
    
    for(int i = 1; i <= MAX_K; i++) {
        f[i] += f[i - 1];
        s[i] += s[i - 1];
    }
    
    int t; scanf("%d", &t);
    while(t--) {
        long long l, r; scanf("%lld%lld", &l, &r);
        
        long long len = r - l + 1;
        long long all = len * (len - 1) * (len - 2) / 6;
        
        
        all -= s[r] - (f[MAX_K] - f[r]) + (s[MAX_K] - s[l - 1]) - s[l - 1] + (f[MAX_K] - f[r]) -  
        
        printf("%lld\n", all);
    }
    return 0;
}
