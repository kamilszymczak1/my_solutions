#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    long long n, k; scanf("%lld%lld", &n, &k);
    vector<long long>x(n);
    for(long long &c : x) {
        scanf("%lld", &c);
    }
    sort(x.begin(), x.end());
    for(int i = 0; i < n; i++) {
        int ind = lower_bound(x.begin(), x.end(), x[i] - k) - x.begin();
        if(ind != n && x[ind] == x[i] - k) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
