#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;


const long long inf = 1ll << 60;
const int MAX_N = 5007;

char a[MAX_N], b[MAX_N];

void test_case() {
    int n; scanf("%d", &n);
    long long x, y; scanf("%lld%lld", &x, &y);
    scanf("%s", a);
    scanf("%s", b);
    vector<int>ind;
    
    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]){ 
            ind.push_back(i);
        }
    }
    
    if(ind.size() == 0) {
        printf("0\n");
        return;
    }
    
    if(ind.size() % 2 == 0) {
        if(x >= y) {
            if(ind.size() > 2) {
                printf("%lld\n", ind.size() / 2 * y);
            } else {
                if(ind[0] + 1 == ind[1]) {
                    printf("%lld\n", min(x, 2 * y));
                } else {
                    printf("%lld\n", y);
                }
            }
        } else {
            int k = ind.size();
            vector<vector<long long>>dp(k + 1, vector<long long>(k / 2 + 1, inf));
            dp[0][0] = dp[1][0] = 0;
            for(int i = 2; i <= k; i++) {
                
                //we can pair it to the last one
                long long dist = ind[i - 1] - ind[i - 2];
                for(int j = 0; j < k / 2; j++)
                    dp[i][j + 1] = min(dp[i][j + 1], dp[i - 2][j] + dist * x);
                
                for(int j = 0; j <= k / 2; j++)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            }
            
            long long answer = inf;
            for(int i = 0; i <= k / 2; i++) {
                if(dp[k][i] != inf) {
                    answer = min(answer, dp[k][i] + (k / 2 - i) * y);
                }
            }
            
            printf("%lld\n", answer);
        }
    } else {
        printf("-1\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
