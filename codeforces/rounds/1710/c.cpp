#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <map>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

const int mod = 998'244'353;
const int MAX_N = 200'007;
char num[MAX_N];

int main() {
    scanf("%s", num);
    int n = strlen(num), num_value = 0;
    for(int i = 0; i < n; i++) {
        num_value = num_value * 2 + (num[i] == '1');
        if(num_value >= mod)
            num_value -= mod;
    }
    reverse(num, num + n);
    for(int i = 0; i < n; i++)
        num[i] -= '0';
    
    vector<vector<int>>dp(2, vector<int>(1 << 3));
    dp[0][0b111] = 1;
    for(int i = 0; i < n; i++) {
        vector<vector<int>>new_dp(2, vector<int>(1 << 3));
        
        for(int a = 0; a < 2; a++) {
            for(int b = 0; b < 2; b++) {
                for(int c = 0; c < 2; c++) {
                    
                    for(int carry = 0; carry < 2; carry++) {
                        
                        for(int mask = 0; mask < (1 << 3); mask++) {
                            
                            int new_mask = mask;
                            
                            if(a != num[i])
                                new_mask = (new_mask & (0b011)) | ((int)(a < num[i]) << 2);
                            
                            if(b != num[i])
                                new_mask = (new_mask & (0b101)) | ((int)(b < num[i]) << 1);
                            
                            if(c != num[i])
                                new_mask = (new_mask & (0b110)) | ((int)(c < num[i]) << 0);
                            
                            int x = a ^ b, y = a ^ c, z = b ^ c;
                            
                            if(x % 2 != (y + z + carry) % 2)
                                continue;
                            
                            int new_carry = (y + z + carry) >= 2;
                            
                            new_dp[new_carry][new_mask] += dp[carry][mask];
                            if(new_dp[new_carry][new_mask] >= mod)
                                new_dp[new_carry][new_mask] -= mod;
                            
                        }
                        
                    }
                }
            }
        }
        
        swap(dp, new_dp);
    }
    
    int all = (num_value * (num_value + 1ll) % mod) * (num_value - 1ll + mod) % mod;
    int add = (num_value + 1ll) * (1ll + 2 * num_value) % mod;
    dp[0][0b111] = (dp[0][0b111] - add + mod) % mod;
    dp[0][0b111] = (dp[0][0b111] * 3ll) % mod;
    printf("%d\n", (all - dp[0][0b111] + mod) % mod);
    
    return 0;
}
