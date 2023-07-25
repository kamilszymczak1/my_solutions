#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    string s; cin >> s;
    if(s.size() >= 3) {
        cout << "NO\n";
    } else {
        if(s.size() == 2 && s[0] == s[1]) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
