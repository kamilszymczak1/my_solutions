#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    bool palindrome = true;
    for(int i = 0; i < n / 2; i++)
        if(s[i] != s[n - 1 - i])
            palindrome = false;
    if(palindrome || k == 0) {
        cout << 1 << '\n';
    } else {
        cout << 2 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
