#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<long long>a(n);
    for(auto &x : a) {
        scanf("%lld", &x);
    }
    while(!a.empty() && a.back() == 0)
        a.pop_back();
    
    if(a.empty()) {
        printf("YES\n");
        return;
    }
    n = a.size();
    for(int i = 0; i < n - 1; i++) {
        if(a[i] <= 0) {
            printf("NO\n");
            return;
        }
        a[i + 1] += a[i];
    }
    
    printf("%s\n", a[n - 1] == 0 ? "YES" : "NO");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
