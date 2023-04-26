#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    vector<long long>a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        b[n - i + 1] = a[i];
    }
    
    vector<long long>c(n + 1), d(n + 1);
    for(int i = 1; i <= n; i++) {
        c[i] = c[i - 1];
        d[i] = d[i - 1];
        c[i] += max(0ll, a[i - 1] - a[i]);
        d[i] += max(0ll, b[i - 1] - b[i]);
    }
    
    for(int i = 0; i < m; i++) {
        int s, t; scanf("%d%d", &s, &t);
        if(s < t) { 
            printf("%lld\n", c[t] - c[s]);
        } else {
            s = n - s + 1;
            t = n - t + 1;
            printf("%lld\n", d[t] - d[s]);
        }
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
