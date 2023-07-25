#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n), last(n, 0), first(n, 1 << 30), occ(n);
    int diff = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
        first[a[i]] = min(first[a[i]], i);
        last[a[i]] = max(last[a[i]], i);
        if(occ[a[i]] == 0)
            diff++;
        occ[a[i]]++;
    }
    
    vector<bool>increasing(n + 1);
    increasing[n - 1] = increasing[n] = true;
    for(int i = n - 2; i >= 0; i--) {
        if(a[i] <= a[i + 1])
            increasing[i] = increasing[i + 1];
        else
            increasing[i] = false;
    }
    
    int result = diff;
    if(increasing[0])
        result = 0;
    
    int mx = -1, op = 0;
    vector<bool>was(n);
    for(int i = 0; i < n; i++) {
        mx = max(mx, last[a[i]]);
        if(!was[a[i]])
            op++;
        was[a[i]] = true;
        
        if(increasing[i + 1] && mx == i)
            result = min(result, op);
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
