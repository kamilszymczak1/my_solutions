#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    long long n; cin >> n;
    for(long long x = 2; x < n; x++) {
        long long y = n - x - 1;
        if(__gcd(x, y) == 1 && y != 0) {
            cout << x << ' ' << y << ' ' << 1 << '\n';
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
