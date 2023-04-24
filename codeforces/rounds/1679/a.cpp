#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>

using namespace std;

void TestCase() {
    long long n; scanf("%lld", &n);
    if(n <= 3 || n % 2 == 1) {
        printf("-1\n");
        return;
    }
    
    long long lo = 1ll << 61;
    long long hi = 0;
    for(int i = 0; i <= 10; i++) {
        if(i * 6 <= n) {
            long long N = n - i * 6;
            if(N % 4 == 0)
                hi = max(hi, N / 4 + i);
            
        }
        
        if(i * 4 <= n) {
            long long N = n - i * 4;
            if(N % 6 == 0)
                lo = min(lo, N / 6 + i);
        }
    }
    
    printf("%lld %lld\n", lo, hi);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
