#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <map>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

bool Check(vector<long long>a, long long n, long long m) {
    long long change = 0, sum = 0;
    for(long long &x : a) {
        x = x / n;
        if(x < 2)
            x = 0;
    }
    sort(a.begin(), a.end());
    int k = a.size();
    for(int i = k - 1; i >= 0; i--) {
        sum += a[i];
        change += max(0ll, a[i] - 2);
        if(sum >= m && sum - change <= m)
            return true;
    }
    return false;
}

void TestCase() {
    long long n, m, k; scanf("%lld%lld%lld", &n, &m, &k);
    vector<long long>a(k);
    for(auto &x : a)
        scanf("%lld", &x);
    if(Check(a, n, m) || Check(a, m, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}

