#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int inf = 1 << 30;

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    long long sum = 0;
    vector<int>a(n);
    for(auto &x : a) {
        scanf("%d", &x);
        sum += abs(x);
    }
    int gcd; scanf("%d", &gcd);
    for(int i = 1; i < m; i++) {
        int x; scanf("%d", &x);
        gcd = __gcd(gcd, x);
    }
    vector<int>lo(gcd, inf), cnt(gcd, 0);
    for(int i = 0; i < n; i++) {
        cnt[i % gcd] += a[i] < 0;
        lo[i % gcd] = min(lo[i % gcd], abs(a[i]));
    }
    
    long long ans1 = sum, ans2 = sum;
    for(int i = 0; i < gcd; i++) {
        
        //we don't change anything
        ans1 -= (cnt[i] % 2) * lo[i] * 2;
        //we change bits
        ans2 -= (1 - cnt[i] % 2) * lo[i] * 2;
        
        
    }
    printf("%lld\n", max(ans1, ans2));
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
