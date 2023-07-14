#include <iostream>

using namespace std;

bool Query();

int main() {
    ios_base::sync_with_stdio(0);
    
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        if(Query())
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    
    return 0;
}

bool Query() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    for(int i = 0; i < n - k; i++) {
        if(s[i] == '?')
            continue;
        if(s[i + k] == '?')
            s[i + k] = s[i];
        else if(s[i + k] != s[i])
            return false;
    }
    for(int i = n - 1; i >= k; i--) {
        if(s[i] == '?')
            continue;
        if(s[i - k] == '?')
            s[i - k] = s[i];
        else if(s[i - k] != s[i])
            return false;
    }
    
    int zeroes = 0;
    int ones = 0;
    
    for(int i = 0; i < k; i++)
        if(s[i] == '1')
            ones++;
        else if(s[i] == '0')
            zeroes++;
        
        if(ones > k / 2 || zeroes > k / 2)
            return false;
        for(int beg = 1; beg <= n - k; beg++) {
            if(s[beg - 1] == '0')
                zeroes--;
            if(s[beg - 1] == '1')
                ones--;
            if(s[beg + k - 1] == '0')
                zeroes++;
            if(s[beg + k - 1] == '1')
                ones++;
            if(ones > k / 2 || zeroes > k / 2)
                return false;
        }
        
        return true;
}
