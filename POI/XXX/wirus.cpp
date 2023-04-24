#include <iostream>
#include <bitset>
#include <algorithm>

using namespace std;

const int L = 64;
const int MAX_N = 707;

bitset<MAX_N>dp[L][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long long d; cin >> d;
    
    if(n == 2) {
        dp[0][0][0] = true;
        dp[0][0][1] = true;
        dp[0][1][0] = true;
    } else {
        for(int i = 0; i < n; i++) {
            dp[0][i][i] = true;
            dp[0][i][i - 1 < 0 ? (i - 1 + n) : (i - 1)] = true;
        }
        dp[0][1][n - 1] = true;
    }
    
    long long d2 = d / n;
    
    for(int b = 1; (1ll << b) <= d2; b++) {
        
        for(int i = 0; i < n; i++) {
            
            for(int j = 0; j < n; j++) {
                
                if(dp[b - 1][i][j]) {
                    dp[b][i] ^= dp[b - 1][j];
                }
                
            }
        }
    }
    
    bitset<MAX_N>answer;
    string s; cin >> s;
    for(int i = 0; i < n; i++)
        answer[i] = s[i] == '1';

    for(int b = 0; (1ll << b) <= d2; b++) {
        if((d2 >> b) & 1) {
            
            bitset<MAX_N>new_answer;
            for(int i = 0; i < n; i++) {
                if(answer[i]) {
                    new_answer ^= dp[b][i];
                }
            }
            
            answer = new_answer;
        }
    }
    
    s = answer.to_string().substr(MAX_N - n, n);
    reverse(s.begin(), s.end());
    
    long long rem = d % n;
    
    int head = 0;
    for(int i = 0; i < rem; i++) {
        int next = head + 1;
        if(next >= n)
            next -= n;
        s[head] = s[head] == s[next] ? '0' : '1';
        head = next;
    }
    for(int i = 0; i < n; i++) {
        int j = head + i;
        if(j >= n)
            j -= n;
        cout << s[j];
    }
    cout << '\n';
    
    return 0;
}
