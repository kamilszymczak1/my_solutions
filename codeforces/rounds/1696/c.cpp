#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

vector<pair<long long, long long>> load(int n, long long m) {
    vector<pair<long long, long long>>a;
    for(int i = 0; i < n; i++) {
        long long x; scanf("%lld", &x);
        long long count = 1;
        while(x % m == 0) {
            x /= m;
            count *= m;
        }
        if(!a.empty() && a.back().first == x) {
            a.back().second += count;
        } else {
            a.emplace_back(x, count);
        }
    }
    return a;
}

void test_case() {
    int n; scanf("%d", &n);
    long long m; scanf("%lld", &m);
    auto a = load(n, m);
    int k; scanf("%d", &k);
    auto b = load(k, m);
    printf("%s\n", a == b ? "Yes" : "No");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
