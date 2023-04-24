#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const long long inf = 1ll << 60;

const int MAX_N = 100'050;
const int MAX_K = 8;

int n, m, k;
vector<int>adj[MAX_N];
long long f[MAX_N];
long long answer[MAX_N];
int my_mask[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++)
        cin >> f[i];
    
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        my_mask[a - 1] |= 1 << (b - a - 1);
        adj[a - 1].push_back(b - 1);
    }
    
    for(int i = n - 1; i >= 0; i--) {
        for(int j : adj[i]) {
            my_mask[i] |= (my_mask[j] << (j - i)) & ((1 << k) - 1); 
        }
    }
    
    vector<long long>dp(1 << k), new_dp(1 << k);
    
    vector<long long>prev_mask(1 << k), new_prev_mask(1 << k);
    
    for(int i = n - 1; i >= 0; i--) {
        
        fill(new_dp.begin(), new_dp.end(), 0);
        
        for(int umask = 0; umask < (1 << (k - 1)); umask++) {
            
            {
                int mask = umask << 1;
                new_prev_mask[mask] = ((prev_mask[mask >> 1] << 1) | (mask >> 1)) & ((1 << k) - 1);
                int real_mask = (new_prev_mask[mask] << 1) & ((1 << k) - 1);
                new_dp[real_mask] = max(new_dp[real_mask], dp[new_prev_mask[mask]]);
            }
            
            {
                int mask = (umask << 1) ^ 1;
                new_prev_mask[mask] = (((prev_mask[mask >> 1] << 1) | (mask >> 1)) & ((1 << k) - 1)) | my_mask[i];
                int real_mask = ((new_prev_mask[mask] << 1) & ((1 << k) - 1)) ^ 1;
                new_dp[real_mask] = max(new_dp[real_mask], dp[new_prev_mask[mask]] + f[i]);
            }
            
        }
        
        answer[i] = new_dp[((my_mask[i] << 1) & ((1 << k) - 1)) ^ 1];
        
        swap(prev_mask, new_prev_mask);
        swap(dp, new_dp);
    }
    
    for(int i = 0; i < n; i++)
        cout << answer[i] << '\n';
    
    return 0;
}
