#include <iostream>

using namespace std;

long long sum_digit_square(long long x) {
    long long result = 0;
    while(x > 0) {
        int d = x % 10;
        result += d * d;
        x /= 10;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    while(n--) {
        string s; cin >> s;
        if(s == "1" || s == "4") {
            cout << (s == "1" ? "1" : "4") << "\n";
            continue;
        }
        long long x = 0;
        for(char c : s) {
            int d = c - '0';
            x += d * d;
        }
        cout << s << ' ';
        while(x != 1 && x != 4) {
            cout << x << ' ';
            x = sum_digit_square(x);
        }
        cout << x << '\n';
    }
}
