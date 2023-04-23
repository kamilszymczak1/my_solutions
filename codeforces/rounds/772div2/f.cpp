#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long F(pair<long long, long long>&a, pair<long long, long long>&b) {
    return abs(a.first - b.first) * (a.second + b.second);
}

template<typename T>
bool cmp(T a, T b) {
    return a.second < b.second;
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
            pair<long long, long long>p = make_pair(x[i], w[i]);
//             printf("at %d s = ", i + 1);
//             for(auto [a, b] : s)
//                 printf("%lld ", b);
//             printf("\n");
            sort(s.begin(), s.end(), cmp<pair<long long, long long>>);
            long long best = 1ll << 62, bestW = 0;
            for(int j = 0; j < (int)s.size())
//             while(!s.empty() && s.back().second >= w[i])
//                 s.pop_back();
            s.emplace_back(x[i], w[i]);
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
