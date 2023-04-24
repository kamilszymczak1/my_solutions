#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 60;

bool CheckMin(int m, vector<int>&x, int l) {
    int n = x.size(), last = 0;
    for(int i = 0; i < n - 1; i++) {
        if(x[i + 1] - last < m)
            return false;
        last = max(x[i], last + m);
    }
    return l - last >= m;
}

bool CheckMax(int m, vector<int>&x, int l) {
    int n = x.size(), last = 0;
    for(int i = 0; i < n - 1; i++) {
        if(x[i] - last > m)
            return false;
        last = min(x[i + 1], last + m);
    }
    return l - last <= m;
}

int main() {
    int l, n; scanf("%d%d", &l, &n);
    vector<int>x(n);
    for(auto &y : x)
        scanf("%d", &y);
    
    if(n == 1) {
        printf("0 %d\n", l);
        return 0;
    }
    
    int lo = 0, hi = (1 << 30) - 1;
    for(int i = 29; i >= 0; i--) {
        lo += 1 << i;
        if(CheckMin(lo, x, l) == false)
            lo -= 1 << i;
        hi -= 1 << i;
        if(CheckMax(hi, x, l) == false)
            hi += 1 << i;
    }
    
    vector<int>a(n + 1), c(n + 1);
    a[n] = c[n] = l;
    for(int i = 1; i <= n - 1; i++) {
        a[i] = max(x[i - 1], a[i - 1] + lo);
    }
    for(int i = n - 1; i >= 0; i--) {
        int y = min(c[i + 1] - a[i], hi);
        c[i] = c[i + 1] - y;
    }
    
    for(int i = 1; i <= n; i++)
        printf("%d %d\n", c[i - 1], c[i]);
    
    return 0;
}
