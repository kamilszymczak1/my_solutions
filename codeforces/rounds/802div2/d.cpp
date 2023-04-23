#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;

long long ceil(long long a, long long b) {
    if(a % b == 0)
        return a / b;
    return a / b + 1;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>v(n);
    for(auto &x : v)
        scanf("%lld", &x);
    int q; scanf("%d", &q);
    vector<pair<int, int>>queries;
    for(int i = 0; i < q; i++) {
        int t; scanf("%d", &t);
        queries.emplace_back(t, i);
    }
    sort(queries.begin(), queries.end());
    long long minT = 0, sum = 0;
    for(int i = 0; i < n; i++) {
        sum += v[i];
        minT = max(minT, ceil(sum, (i + 1)));
    }
    long long k = n - 1;
    vector<int>ans(q);
    for(auto [t, id] : queries) {
        if(t < minT) {
            ans[id] = -1;
            continue;
        }
        while(t * k >= sum)
            k--;
        ans[id] = k + 1;
    }
    for(int x : ans)
        printf("%d\n", x);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
