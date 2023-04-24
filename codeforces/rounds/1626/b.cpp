#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    string s; cin >> s;
    int lastTwo = -1;
    int firstOne = -1;
    int n = s.size();
    for(int i = 0; i < n - 1; i++) {
        if(s[i] - '0' + s[i + 1] - '0' >= 10)
            lastTwo = i;
        else if(firstOne == -1)
            firstOne = i;
    }
    if(lastTwo != -1) {
        int sum = s[lastTwo] - '0' + s[lastTwo + 1] - '0';
        s[lastTwo] = sum / 10 + '0';
        s[lastTwo + 1] = (sum % 10) + '0';
        cout << s << '\n';
    } else {
        for(int i = 0; i < firstOne; i++)
            cout << s[i];
        cout << s[firstOne] + s[firstOne + 1] - 2 * ('0');
        for(int i = firstOne + 2; i < n; i++)
            cout << s[i];
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
