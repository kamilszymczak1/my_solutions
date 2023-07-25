#include <iostream>
#include <set>
    
using namespace std;
    
const string s[3] = {
    "QWERTYUIOP",
    "ASDFGHJKL",
    "ZXCVBNM"
};
    
bool ok[256];
    
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    set<int>all_s;
    for(int i = 0; i < 3; i++) {
        string t; cin >> t;
        for(int j = 0; j < (int)t.size(); j++) {
            if(t[j] == '*') {
                ok[s[i][j]] = true;
                all_s.insert(s[i][j]);
            }
        }
    }
    int q; cin >> q;
    while(q--) {
        bool answer = true;
        string t; cin >> t;
        set<int>my_s;
        for(char c : t) {
            my_s.insert(c);
        }
        cout << (my_s == all_s ? "POSSIBLE" : "IMPOSSIBLE") << '\n';
    }
}
