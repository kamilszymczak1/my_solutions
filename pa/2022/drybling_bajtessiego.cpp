#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

const long long mod = 1'000'000'007;

const int H = 602;

long long left_dp[H][2];
long long right_dp[H][H][2];
long long my_dp[H][2];
long long basic[H];

int main() {
    int n; cin >> n;
    
    vector<string>t(n);
    for(string &s : t)
        cin >> s;
    
    for(int i = 0; i < n; i++) {
        right_dp[i][0][1] = 1;
        string s = t[i];
        reverse(s.begin(), s.end());
        
        for(char c : s) {
            
            for(int j = 0; j < H; j++)
                my_dp[j][0] = my_dp[j][1] = 0;
            
            if(c == 'L') {
                for(int j = 0; j < H; j++) {
                    my_dp[j][1] = right_dp[i][j][1];
                    if(j + 1 < H) {
                        my_dp[j][0] = right_dp[i][j + 1][0];
                        my_dp[j][1] += right_dp[i][j + 1][0];
                        if(my_dp[j][1] >= mod)
                            my_dp[j][1] -= mod;
                    }
                }
                basic[i] += right_dp[i][1][0];
                if(basic[i] >= mod)
                    basic[i] -= mod;
            } else {
                for(int j = 0; j < H; j++) {
                    my_dp[j][0] = right_dp[i][j][0];
                    if(j - 1 >= 0) {
                        my_dp[j][1] = right_dp[i][j - 1][1];
                        my_dp[j][0] += right_dp[i][j - 1][1];
                        if(my_dp[j][0] >= mod)
                            my_dp[j][0] -= mod;
                    }
                }
            }
            swap(my_dp, right_dp[i]);
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < H; j++)
            left_dp[j][0] = left_dp[j][1] = 0;
        for(char c : t[i]) {
            for(int j = 0; j < H; j++)
                my_dp[j][0] = my_dp[j][1] = 0;
            if(c == 'L') {
                my_dp[0][0] = 0;
                my_dp[0][1] = left_dp[0][1];
                for(int i = 1; i < H; i++) {
                    my_dp[i][1] = left_dp[i][1];
                    my_dp[i][0] += left_dp[i - 1][0] + left_dp[i - 1][1] + (i == 1 ? 1 : 0);
                    if(my_dp[i][0] >= mod)
                        my_dp[i][0] -= mod;
                }
            } else {
                for(int i = 0; i < H - 1; i++) {
                    my_dp[i][0] = left_dp[i][0];
                    my_dp[i][1] += left_dp[i + 1][0] + left_dp[i + 1][1];
                    if(my_dp[i][1] >= mod)
                        my_dp[i][1] -= mod;
                }
                my_dp[H - 1][0] = left_dp[H - 1][0];
                my_dp[H - 1][1] = 0;
            }
            
            swap(left_dp, my_dp);
        }
        
        
        for(int j = 0; j < n; j++) {
            
            long long answer = basic[j];
            
            for(int k = 0; k < H; k++) {
                answer = (answer + left_dp[k][0] * right_dp[j][k][0] + left_dp[k][1] * right_dp[j][k][1]) % mod;
            }
            
            cout << answer << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}
