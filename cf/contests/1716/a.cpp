#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

void test_case() {
    long long n; scanf("%lld", &n);
    long long result = 1ll << 60;
    
    for(int i = -5; i <= 5; i++) {
        long long moves = abs(i);
        
        long long pos = i * 2;
        long long dist = abs(pos - n);
        if(dist % 3 == 0)
            result = min(result, abs(i) + dist / 3);
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
