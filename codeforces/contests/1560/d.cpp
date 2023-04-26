#include <algorithm>
#include <iostream>

using namespace std;

string NumberToString(long long n) {
    string result = "";
    while(n) {
        result += (char)(n % 10 + '0');
        n /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

int Solve(string s, string t) {
    for(int i = t.size(); i > 0; i--) {
        string x = t.substr(0, i);
        int pos = -1;
        for(char c : x) {
            pos++;
            while(pos < s.size() && s[pos] != c)
                pos++;
        }
        if(pos < s.size()) {
            return (int)s.size() + (int)t.size() - 2 * i;
        }
        
    }
    return (int)s.size() + (int)t.size();
}

void TestCase() {
    int n; cin >> n;
    string s = NumberToString(n);
    long long p2 = 1;
    int result = 1000;
    for(int i = 0; i < 60; i++) {
        string t = NumberToString(p2);
        result = min(result, Solve(s, t));
        p2 <<= 1;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
