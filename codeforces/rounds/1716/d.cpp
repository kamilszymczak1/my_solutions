#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const long long mod = 998244353;

void test_case() {
    int n, k; scanf("%d%d", &n, &k);
    vector<int>dp(n + 1);
    vector<int>to_add(n + 1);
    vector<int>answer(n + 1);
    dp[0] = 1;
    int offset = 0;
    for(int t = k; t + offset <= n; t++) {
        
        
        for(int i = offset; i + t <= n; i++) {
            to_add[i + t] += dp[i];
            if(to_add[i + t] >= mod)
                to_add[i + t] -= mod;
            to_add[i + t] += to_add[i];
            if(to_add[i + t] >= mod)
                to_add[i + t] -= mod;
        }
        
        for(int i = offset; i <= n; i++) {
            answer[i] += dp[i];
            if(answer[i] >= mod)
                answer[i] -= mod;
            dp[i] = to_add[i];
            to_add[i] = 0;
        }
        
        offset += t;
    }
    
    for(int i = 0; i <= n; i++) {
        answer[i] += dp[i];
        if(answer[i] >= mod)
            answer[i] -= mod;
    }
    
    for(int i = 1; i <= n; i++)
        printf("%d ", answer[i]);
    printf("\n");
}

int main() {
    int t = 1;
    while(t--)
        test_case();
}
