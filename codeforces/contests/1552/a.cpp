#include <iostream>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    string s; cin >> s;
    string s2 = s;
    sort(s2.begin(), s2.end());
    int result = 0;
    for(int i = 0; i < n; i++)
        result += s[i] != s2[i];
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
