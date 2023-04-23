#include <cstdio>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const long long mod = 1'000'000'007;

void test_case() {
    int n; scanf("%d", &n);
    vector<pair<int, int>>p(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i].first);
        p[i].second = i;
    }
    sort(p.begin(), p.end());
    int l = p[0].second, r = p[0].second;
    long long result = 1;
    for(int i = 1; i < n; i++) {
        if(p[i].second < l || p[i].second > r) {
            l = min(l, p[i].second);
            r = max(r, p[i].second);
        } else {
            result = result * (r - l + 1 - i) % mod;
        }
    }
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

