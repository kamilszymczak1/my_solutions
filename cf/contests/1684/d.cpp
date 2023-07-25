#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <cstring>

using namespace std;

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    vector<long long>best;
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        long long a; scanf("%lld", &a);
        sum += a;
        best.push_back(a - (n - i));
    }
    sort(best.begin(), best.end(), greater<long long>());
    long long current = 0;
    long long result = 1ll << 60;
    for(long long i = 0; i <= (long long)k; i++) {
        
        result = min(result, sum - current - i * (i - 1) / 2);
        
        if(i < n)
            current += best[i];
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
