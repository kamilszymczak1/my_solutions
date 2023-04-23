#include <iostream>

using namespace std;

int Query();

int main() {
    ios_base::sync_with_stdio(0);
    
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++)
        cout << Query() << "\n";
    
    return 0;
}

int Query() {
    int n;
    string s;
    
    cin >> n >> s;
    
    int prefix = 0, pos = 0, result = 0;
    bool backTrack = false;
    
    while(prefix <= pos && prefix < n) {
        while(!backTrack && pos < n - 1 && s[pos] != s[pos + 1])
            pos++;
        while(prefix < n - 1 && s[prefix] == s[prefix + 1])
            prefix++;
        prefix++;
        if(backTrack)
            pos--;
        else if(pos >= n - 1)
            backTrack = true, pos--;
        else
            pos = max(pos + 1, prefix);
        result++;
    }
    
    return result;
}
