#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>

using namespace std;

void TestCase() {
    int n, q; scanf("%d%d", &n, &q);
    vector<pair<long long, int>>v(n);
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &v[i].first);
        sum += v[i].first;
        v[i].second = -1;
    }
    int lastChange = -1;
    long long lastAll = 0;
    for(int z = 0; z < q; z++) {
        int t; scanf("%d", &t);
        if(t == 1) {
            int i; long long x; scanf("%d%lld", &i, &x); i--;
            if(v[i].second < lastChange) {
                sum += x - lastAll;
            } else {
                sum += x - v[i].first;
            }
            v[i].first = x;
            v[i].second = z;
        } else {
            scanf("%lld", &lastAll);
            sum = n * lastAll;
            lastChange = z;
        }
        printf("%lld\n", sum);
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
