#include <iostream>

using namespace std;

bool appeared[26];

bool TestCase() {
    fill(appeared, appeared + 26, false);
    int n; string s;
    cin >> n >> s;
    for(int i = 0; i < n; i++) {
        if(appeared[s[i] - 'A'])
            return false;
        appeared[s[i] - 'A'] = true;
        while(i < n - 1 && s[i] == s[i + 1])
            i++;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        cout << (TestCase() ? "YES\n" : "NO\n") << '\n';
    }
    
    
    return 0;
}
