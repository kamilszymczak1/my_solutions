#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int f(char a, char b, char c) {
    a -= '0';
    b -= '0';
    c -= '0';
    return a * 100 + b * 10 + c;
}

int main() {
    ios_base::sync_with_stdio(0);
    string s; cin >> s;
    char a = s[0], b = s[1], c = s[2];
    int result = f(a, b, c);
    result += f(b, c, a);
    result += f(c, a, b);
    cout << result << '\n';
    return 0;
}
