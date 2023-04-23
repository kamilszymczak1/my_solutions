#include <algorithm>
#include <iostream>
#include <vector>
    
using namespace std;
    
int k, max_k;
int l[7], new_l[7];
    
bool compare(int my_mask, int next_mask) {
    int my_one = 0;
    int next_one = 0;
    for(int i = max_k - 1; i >= 0; i--) {
        my_one += (my_mask >> i) & 1;
        next_one += (next_mask >> i) & 1;
        if(next_one > my_one)
            return false;
    }
    return true;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    while(cin >> k) {
        for(int i = 0; i < 7; i++)
            new_l[i] = 0;
        for(int i = 0; i < k; i++) {
            cin >> l[i];
            for(int j = 0; j < l[i]; j++)
                new_l[j]++;
        }
        cin >> max_k;
        k = l[0];
        swap(l, new_l);
        
        vector<vector<int>>masks(max_k + 1);
        for(int i = 0; i < (1 << max_k); i++)
            masks[__builtin_popcount(i)].push_back(i);
            
        vector<long long>dp(1 << max_k);
        for(int mask : masks[l[0]])
            dp[mask] = 1;
            
        for(int i = 0; i < k - 1; i++) {
            vector<long long>new_dp(1 << max_k);
            
            for(int my_mask : masks[l[i]]) {
                for(int next_mask : masks[l[i + 1]]) {
                    if(compare(my_mask, next_mask))
                        new_dp[next_mask] += dp[my_mask];
                }
            }
            
            swap(dp, new_dp);
        }
        
        long long answer = 0;
        for(long long x : dp)
            answer += x;
        cout << answer << '\n';
    }
    
}
