#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    string s; cin >> s;
    vector<int>cnt(26);
    for(char c : s)
        cnt[c - 'a']++;
    int j = 0;
    for(int i = 0; i < 26; i++) {
        if(cnt[i] == 2) {
            s[j] = s[j + 1] = i + 'a';
            j += 2;
        } else if(cnt[i] == 1) {
            s[j] = i + 'a';
            j++;
        }
    }
    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
