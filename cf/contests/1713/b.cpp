#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cmath>
#include <cstring>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    vector<bool>increasing(n, false);
    increasing[0] = true;
    for(int i = 1; i < n; i++) {
        if(a[i] >= a[i - 1] && increasing[i - 1]) {
            increasing[i] = true;
        }
    }
    vector<bool>decreasing(n, false);
    decreasing[n - 1] = true;
    for(int i = n - 2; i >= 0; i--) {
        if(a[i] >= a[i + 1] && decreasing[i + 1]) {
            decreasing[i] = true;
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(increasing[i] && decreasing[i]) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
