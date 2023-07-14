#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    string s; cin >> s;
    vector<bool>keys(3, false);
    for(int i = 0; i < 6; i++) {
        if('a' <= s[i] && s[i] <= 'z') {
            int x = 0;
            if(s[i] == 'g')
                x = 1;
            if(s[i] == 'b')
                x = 2;
            keys[x] = true;
        } else {
            int x = 0;
            if(s[i] == 'G')
                x = 1;
            if(s[i] == 'B')
                x = 2;
            if(keys[x] == false) {
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
