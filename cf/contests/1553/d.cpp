#include <iostream>

using namespace std;

bool Check(int pos, string s, string t) {
    bool result = true;
    for(char c : t) {
        int current = pos;
        while(pos < s.size() && (s[pos] != c || (s[pos] == c && ((pos - current) % 2 != 0))))
            pos++;
        if(pos == s.size())
            result = false;
        pos++;
    }
    if((s.size() - pos) % 2 != 0)
        result = false;
    return result;
}

void TestCase() {
    string s, t; cin >> s >> t;
    bool oddOK = false, evenOK = false, result = false;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == t[0]) {
            if(i % 2 == 0) {
                if(!evenOK) {
                    result |= Check(i, s, t);
                    evenOK = true;
                }
            } else {
                if(!oddOK) {
                    result |= Check(i, s, t);
                    oddOK = true;
                }
            }
        }
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
