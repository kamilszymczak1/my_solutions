#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void TestCase() {
    int n; cin >> n;
    string s; cin >> s;
    if(n == 1) {
        cout << s[0] << s[0] << '\n';
        return;
    }
    if(s[0] == s[1]) {
        cout << s[0] << s[1] << '\n';
        return;
    }
    if(s[1] > s[0]) {
        cout << s[0] << s[0] << '\n';
        return;
    }
    int i = 0;
    while(i < n - 1 && s[i] >= s[i + 1])
        i++;
    for(int j = 0; j <= i; j++)
        cout << s[j];
    for(int j = i; j >= 0; j--)
        cout << s[j];
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
