#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

void TestCase() {
    int n, C; scanf("%d%d", &n, &C);
    vector<long long>best(C + 1, -1);
    for(int i = 0; i < n; i++) {
        long long c, d, h; scanf("%lld%lld%lld", &c, &d, &h);
        best[c] = max(best[c], d * h);
    }
    
    vector<long long>biggest(C + 1, 0);
    for(long long c = 1; c <= C; c++) {
        long long p = best[c];
        if(p == -1)
            continue;
        for(long long n = 1; n * c <= C; n++) {
            biggest[c * n] = max(biggest[c * n], n * p - 1);
        }
    }
    for(int i = 1; i <= C; i++)
        biggest[i] = max(biggest[i], biggest[i - 1]);
    int m; scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        long long a, b; scanf("%lld%lld", &a, &b);
        int x = lower_bound(biggest.begin(), biggest.end(), a * b) - biggest.begin();
        if(x == C + 1)
            x = -1;
        printf("%d ", x);
    }
    printf("\n");
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}

