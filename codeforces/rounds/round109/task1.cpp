#include <iostream>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void TestCase() {
    int k; cin >> k;
    cout << 100 / gcd(k, 100 - k) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        TestCase();
    }
    return 0;
}
