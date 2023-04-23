#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

const int MAX_A = 3001, inf = 1 << 29;

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    int result = inf;
    for(int mn = 1; mn <= a[0]; mn++) {
        int mx = mn;
        for(int i = 0; i < n; i++) {
            int maxP = min(a[i] / mn, k);
            mx = max(mx, a[i] / maxP);
        }
        if(mx >= mn)
            result = min(result, mx - mn);
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
