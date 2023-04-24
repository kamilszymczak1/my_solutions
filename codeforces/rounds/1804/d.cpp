#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

void get(string &s, int n, int &lo, int &hi) {
    
    int my_lo = 0, my_hi = 0;
    
    vector<int>dp1(n + 1), dp2(n + 1);
    
    for(int i = 2; i <= n; i++) {
        
        dp1[i] = max(dp1[i], dp1[i - 1]);
        dp2[i] = max(dp2[i], dp2[i - 1]);
        
        if(s[i - 1] == s[i - 2] && s[i - 1] == '1') {
            dp1[i] = max(dp1[i], dp1[i - 2] + 1);
        } else {
            dp2[i] = max(dp2[i], dp2[i - 2] + 1);
        }
    }
    
    int one_count = 0;
    for(int i = 0; i < n; i++)
        one_count += s[i] == '1';
    
    lo += one_count - min(n / 4, dp1[n]);
    hi += one_count - n / 4 + min(n / 4, dp2[n]);
}

void test_case() {
    int n, m; cin >> n >> m;
    int lo = 0, hi = 0;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        get(s, m, lo, hi);
    }
    cout << lo << ' ' << hi << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        test_case();
    return 0;
}

