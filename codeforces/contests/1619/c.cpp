#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool Check(string a, string b, string c) {
    if(a.size() < b.size())
        swap(a, b);
    while(b.size() != a.size())
        b = '0' + b;
    string s = "";
    for(int i = a.size() - 1; i >= 0; i--) {
        if(a[i] - '0' + b[i] - '0' < 10) {
            s = (char)(a[i] + b[i] - '0') + s;
        } else {
            s = (char)(a[i] + b[i] - 10 - '0') + s;
            s = '1' + s;
        }
    }
    return s == c;
}

string TestCase() {
    string a, s; cin >> a >> s;
    int last = a.size() - 1;
    string b = "";
    for(int i = s.size() - 1; i >= 0; i--) {
        if(last < 0) {
            b = s[i] + b;
        } else {
            if(s[i] < a[last]) {
                if(i == 0 || s[i - 1] != '1')
                    return "-1";
                b = (char)(s[i] - a[last] + 10 + '0') + b;
                i--;
            } else {
                b = (char)(s[i] - a[last] + '0') + b;
            }
            last--;
        }
    }
    while(!b.empty() && b[0] == '0')
        b = b.substr(1, b.size() - 1);
    if(last == -1 && Check(a, b, s))
        return b;
    return "-1";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        cout << TestCase() << '\n';
    
    return 0;
}
