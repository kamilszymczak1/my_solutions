#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    long long a, b; scanf("%lld%lld", &a, &b);
    vector<long long>x(n);
    for(auto &y : x)
        scanf("%lld", &y);
    
    long long capital = 0, ans = 0;
    for(int i = 0; i < n; i++) {
        ans += b * (x[i] - capital);
        long long kingdomsLeft = n - i - 1;
        if(kingdomsLeft * b > a) {
            ans += a * (x[i] - capital);
            capital = x[i];
        }
    }
    printf("%lld\n", ans);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
