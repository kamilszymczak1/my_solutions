#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int>KMP (string a, string b) {
    string s = a + '#' + b;
    vector<int>border(s.size() + 1, 0);
    int t = border[0] = -1;
    for(int i = 1; i <= s.size(); i++) {
        while(t != -1 && s[t] != s[i - 1])
            t = border[t];
        border[i] = ++t;
    }
    return border;
}

bool Check(string s, string prefix, string suffixRev) {
    
    int n = prefix.size(), m = suffixRev.size();
    
    vector<int>A = KMP(prefix, s);
    vector<int>B = KMP(suffixRev, s);
    
    if(n == 0) {
        for(int i = 0; i < s.size(); i++) {
            if(B[i + m + 2] == m) {
                return true;
            }
        }
        return false;
    }
    
    if(m == 0) {
        for(int i = 0; i < s.size(); i++) {
            if(A[i + n + 2] == n) {
                return true;
            }
        }
        return false;
    }
    
    for(int i = 1; i < s.size(); i++) {
        if(A[i + n + 2] == n && B[i + m + 1] == m) {
            return true;
        }
    }
    
    return false;
}

void TestCase() {
    string s, t; cin >> s >> t;
    bool result = false;
    for(int i = 0; i <= t.size(); i++) {
        string prefix = t.substr(0, i);
        string suffixRev = t.substr(i, t.size() - i);
        reverse(suffixRev.begin(), suffixRev.end());
        result |= Check(s, prefix, suffixRev);
    }
    cout << (result ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) 
        TestCase();
    return 0;
}
