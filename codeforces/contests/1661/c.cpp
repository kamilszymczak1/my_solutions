#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long GetMin(long long a, long long b) {
    if(a < b)
        return b * 2 - 1;
    if(a == b)
        return a * 2;
    long long result = max(a * 2, b * 2 - 1);
    long long k = (a - b) / 3;
    for(long long i = max(0ll, k - 3); i <= k + 3; i++) {
        long long A = a - i, B = b + 2 * i;
        result = min(result, max(A * 2, B * 2 - 1));
    }
    return result;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>h(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &h[i]);
    sort(h.begin(), h.end());
    long long a = 0, b = 0;
    for(int i = 0; i < n; i++) {
        long long d = h.back() - h[i];
        a += d / 2;
        b += d % 2;
    }
    
    long long result = min(GetMin(a, b), GetMin(a + b, n - b));
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
