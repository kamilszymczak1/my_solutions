#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    long long x;
    int n; scanf("%d%lld", &n, &x);
    vector<long long>a(n);
    long long result = 0;
    long long maxA = 0, minA = 1 << 30;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        maxA = max(maxA, a[i]);
        minA = min(minA, a[i]);
    }
    for(int i = 0; i < n - 1; i++) {
        long long A = min(a[i], a[i + 1]);
        long long B = max(a[i], a[i + 1]);
        result += B - A;
    }
    result += min((minA - 1) * 2, min(a[0] - 1, a[n - 1] - 1));
    result += min(max(0ll, x - maxA) * 2, min(max(0ll, x - a[0]), max(0ll, x - a[n - 1])));
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
