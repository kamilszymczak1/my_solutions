#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long F(pair<long long, long long>a, pair<long long, long long>b) {
    return abs(a.first - b.first) * (a.second + b.second);
}

void TestCase() {
    int n, q; scanf("%d%d", &n, &q);
    vector<long long>x(n), w(n);
    for(int i = 0; i < n; i++)
        scanf("%lld%lld", &x[i], &w[i]);
    while(q--) {
        int l, r; scanf("%d%d", &l, &r); l--; r--;
        vector<pair<long long, long long>>s;
        long long result = 1ll << 62;
        for(int i = l; i <= r; i++) {
            for(int j = i + 1; j <= r; j++)
                result = min(result, F(make_pair(x[i], w[i]), make_pair(x[j], w[j])));
        }
        printf("%lld\n", result);
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
