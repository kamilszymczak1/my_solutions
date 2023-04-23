#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        vector<long long>a(n);
        for(auto &x : a)
            scanf("%lld", &x);
        sort(a.begin(), a.end());
        printf("%lld\n", a[n - 1] + a[n - 2] - a[0] - a[1]);
    }
}
