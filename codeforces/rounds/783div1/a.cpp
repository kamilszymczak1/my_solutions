#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const long long inf = 1ll << 60;

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>a(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    long long ans = inf;
    for(int i = 0; i < n; i++) {
        long long local = 0, last = 0;
        for(int j = i - 1; j >= 0; j--) {
            long long c = last / a[j] + 2;
            while(c * a[j] >= last)
                c--;
            last = c * a[j];
            local += abs(c);
        }
        last = 0;
        for(int j = i + 1; j < n; j++) {
            long long c = last / a[j] - 2;
            while(c * a[j] <= last)
                c++;
            last = c * a[j];
            local += abs(c);
        }
        ans = min(ans, local);
    }
    printf("%lld\n", ans);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
