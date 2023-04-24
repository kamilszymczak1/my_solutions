#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

long long Cost(vector<long long>&h, int i) {
    long long m = max(h[i + 1], h[i - 1]);
    return max(0ll, m - h[i] + 1);
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>h(n + 2);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &h[i]);
    if(n % 2 == 1) {
        long long result = 0;
        for(int i = 2; i < n; i += 2)
            result += Cost(h, i);
        printf("%lld\n", result);
        return;
    }
    vector<long long>pref(n + 2), suff(n + 2);
    for(int i = 2; i <= n + 1; i++) {
        pref[i] = pref[i - 2] + Cost(h, i);
    }
    
    for(int i = n - 1; i > 1; i--) {
        suff[i] = suff[i + 2] + Cost(h, i);
    }
    
    long long result = 1ll << 60;
    for(int i = 1; i <= n - 1; i += 2) {
        result = min(result, pref[i - 1] + suff[i + 2]);
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
