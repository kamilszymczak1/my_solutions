#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    long long a, b, c; cin >> a >> b >> c;
    if((c + a) % (2 * b) == 0) {
        cout << "YES\n";
    } else if((2 * b - a) > 0 && (2 * b - a) % c == 0) {
        cout << "YES\n";
    } else if((2 * b - c) > 0 && (2 * b - c) % a == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
