#include <iostream>
#include <vector>
    
using namespace std;
    
const int MAX_N = 507, MAX_M = 30, MAX_K = 307;
    
const int mod = 998'244'353;
    
int mod_pow(int x, int exp) {
    if(exp == 0)
        return 1;
    int result = mod_pow(x, exp >> 1);
    result = 1ll * result * result % mod;
    if(exp & 1)
        result = 1ll * x * result % mod;
    return result;
}
    
int inv(int x) {
    return mod_pow(x, mod - 2);
}
    
int n, m, k;
    
int a[MAX_N][MAX_M], factorial[MAX_N], bag[MAX_M][MAX_K];
int p[MAX_N][MAX_K], sum[MAX_N], answer[MAX_N], p_sum_up[MAX_N][MAX_K], p_sum_down[MAX_N][MAX_K];
int inv_factorial[MAX_N];
vector<int>others[MAX_N];
    
int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m >> k;
    
    factorial[0] = 1;
    for(int i = 1; i <= m; i++)
        factorial[i] = 1ll * factorial[i - 1] * i % mod;
    for(int i = 0; i <= m; i++)
        inv_factorial[i] = inv(factorial[i]);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    
    for(int problem_id = 0; problem_id < m; problem_id++) {
        
        for(int i = 0; i < n; i++)
            fill(p[i], p[i] + k + 1, 0);
        
        for(int i = 0; i < n; i++) {
            
            if(a[i][problem_id] == 0) {
                continue;
            }
            
            vector<int>others;
            for(int j = 0; j < m; j++) {
                if(j == problem_id || a[i][j] == 0)
                    continue;
                others.push_back(a[i][j]);
            }
            
            int others_count = others.size();
            
            for(int j = 0; j <= others_count; j++)
                fill(bag[j], bag[j] + k + 1, 0);
            
            bag[0][0] = 1;
            
            for(int x : others) {
                for(int j = others_count - 1; j >= 0; j--) {
                    for(int t = k - x; t >= 0; t--) {
                        bag[j + 1][t + x] += bag[j][t];
                        if(bag[j + 1][t + x] >= mod)
                            bag[j + 1][t + x] -= mod;
                    }
                }
            }
            
            for(int j = k; j - a[i][problem_id] >= 0; j--) {
                
                for(int left = 0; left <= others_count; left++) {
                    int right = others_count - left;
                    int to_add = 1ll * factorial[left] * factorial[right] % mod;
                    p[i][j] += 1ll * bag[left][j - a[i][problem_id]] * to_add % mod;
                    if(p[i][j] >= mod)
                        p[i][j] -= mod;
                }
                
                p[i][j] = 1ll * p[i][j] * inv_factorial[others_count + 1] % mod;
            }
            
        }
        
        for(int i = 0; i < n; i++) {
            int sum = 1;
            for(int j = 0; j <= k; j++) {
                p_sum_up[i][j] = p_sum_down[i][j] = sum;
                sum -= p[i][j];
                if(sum < 0)
                    sum += mod;
            }
        }
        
        for(int i = 1; i < n; i++) {
            for(int j = 0; j <= k; j++) {
                p_sum_up[i][j] = 1ll * p_sum_up[i][j] * p_sum_up[i - 1][j] % mod;
            }
        }
        
        for(int i = n - 2; i >= 0; i--) {
            for(int j = 0; j <= k; j++) {
                p_sum_down[i][j] = 1ll * p_sum_down[i][j] * p_sum_down[i + 1][j] % mod;
            }
        }
        
        
        for(int i = 0; i < n; i++) {
            fill(sum, sum + n, 1);
            for(int j = 1; j <= k; j++) {
                int product = 1;
                if(i != 0)
                    product = 1ll * product * p_sum_up[i - 1][j] % mod;
                if(i != n - 1)
                    product = 1ll * product * p_sum_down[i + 1][j] % mod;
                answer[i] += 1ll * p[i][j] * product % mod;
                if(answer[i] >= mod)
                    answer[i] -= mod;
            }
        }
        
    }
    
    for(int i = 0; i < n; i++)
        cout << answer[i] << '\n';
    
    return 0;
}
