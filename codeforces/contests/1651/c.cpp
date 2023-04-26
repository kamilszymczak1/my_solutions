#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long Best(long long t, vector<int>&x) {
    int ind = upper_bound(x.begin(), x.end(), t) - x.begin();
    if(ind == x.size())
        ind--;
    long long result = 1ll << 60;
    for(int i = 0; i < 3 && ind >= 0; i++) {
        result = min(result, abs(t - x[ind]));
        ind--;
    }
    return result;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &b[i]);
    long long x1 = a[0], x2 = a[n - 1];
    long long y1 = b[0], y2 = b[n - 1];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    long long result = abs(x1 - y1) + abs(x2 - y2);
    result = min(result, abs(x1 - y2) + abs(x2 - y1));
    
    long long X1 = Best(x1, b);
    long long X2 = Best(x2, b);
    long long Y1 = Best(y1, a);
    long long Y2 = Best(y2, a);
    
    result = min(result, abs(x1 - y1) + X2 + Y2);
    result = min(result, abs(x2 - y2) + X1 + Y1);
    result = min(result, abs(x1 - y2) + X2 + Y1);
    result = min(result, abs(x2 - y1) + X1 + Y2);
    result = min(result, X1 + X2 + Y1 + Y2);
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
