#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    string s; cin >> s;
    int n = s.size();
    if(n % 2 == 1) {
        cout << "NO\n";
        return;
    } else {
        for(int i = 0; i < n / 2; i++) {
            if(s[i] != s[i + n / 2]) {
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
