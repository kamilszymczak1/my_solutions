#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>v(n + 1), pref(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
        pref[i] = pref[i - 1] ^ v[i];
    }
    
    vector<int>dp(n + 1, 1 << 30);
    dp[0] = 0;
    
    map<int, int>m;
    m[0] = 0;
    
    for(int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + 1;
        
        if(m.find(pref[i]) != m.end()) {
            dp[i] = min(dp[i], m[pref[i]] + i - 1);
            
            m[pref[i]] = min(m[pref[i]], dp[i] - i);
        } else {
            m[pref[i]] = dp[i] - i;
        }
    }
    printf("%d\n", dp[n]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
