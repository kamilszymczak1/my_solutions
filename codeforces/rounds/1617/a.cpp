#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    string s, t; cin >> s >> t;
    vector<int>cnt(26);
    for(char c : s)
        cnt[c - 'a']++;
    
    if(t == "abc") {
        if(cnt[0] != 0 && cnt[1] != 0 && cnt[2] != 0) {
            int i = 0;
            while(cnt[0]) {
                s[i++] = 'a';
                cnt[0]--;
            }
            while(cnt[2]) {
                s[i++] = 'c';
                cnt[2]--;
            }
            while(cnt[1]) {
                s[i++] = 'b';
                cnt[1]--;
            }
            for(int j = 3; j < 26; j++) {
                while(cnt[j]) {
                    s[i++]= (char)(j + 'a');
                    cnt[j]--;
                }
            }
        } else {
            sort(s.begin(), s.end());
        }
    } else {
        sort(s.begin(), s.end());
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
