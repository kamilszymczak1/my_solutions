#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
    
using namespace std;
    
const long long inf = 1ll << 60;
    
bool match(int a, int b) {
    return (a ^ 1) == b;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<long long, int>>c(2 * n);
    for(int i = 0; i < 2 * n; i++) {
        cin >> c[i].first;
        c[i].second = i;
    }
    sort(c.begin(), c.end());
    const int B = 4;
    vector<vector<long long>>dp(2 * n + 1, vector<long long>(1 << B, inf));
    
    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 4; j++) {
            if(!match(c[i].second, c[j].second)) {
                dp[4][(1 << i) | (1 << j)] = min(dp[4][(1 << i) | (1 << j)], abs(c[i].first - c[j].first));
            }
        }
    }
    
    for(int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 4; j++) {
            if(match(c[i].second, c[j].second))
                continue;
            
            for(int k = 0; k < 4; k++) {
                if(k == i || k == j)
                    continue;
                
                for(int t = k + 1; t < 4; t++) {
                    if(t == i || t == j || match(c[k].second, c[t].second))
                        continue;
                    
                    dp[4][0b1111] = min(dp[4][0b1111], abs(c[k].first - c[t].first) + abs(c[i].first - c[j].first));
                }
            }
        }
    }
    
    for(int i = B; i < 2 * n; i++) {
        for(int prev_mask = 0; prev_mask < (1 << B); prev_mask++) {
            
            for(int prev_ele = 0; prev_ele < B; prev_ele++) {
                
                if((prev_mask & (1 << prev_ele)) != 0)
                    continue;
                
                int j = i - B + prev_ele;
                
                if(match(c[i].second, c[j].second))
                    continue;
                
                int new_mask = prev_mask | (1 << prev_ele);
                
                if((new_mask & 1) == 0)
                    continue;
                
                dp[i + 1][(new_mask >> 1) | (1 << (B - 1))] = min(
                    dp[i + 1][(new_mask >> 1) | (1 << (B - 1))],
                    dp[i][prev_mask] + abs(c[i].first - c[j].first));
                
            }
            
            if(prev_mask & 1)
                dp[i + 1][prev_mask >> 1] = min(dp[i + 1][prev_mask >> 1], dp[i][prev_mask]);
            
        }
    }
    
    cout << dp[2 * n][0b1111] << '\n';
    
    
    return 0;
}
