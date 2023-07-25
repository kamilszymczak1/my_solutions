#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long l, r; cin >> l >> r;
    long long result = 0;
    for(long long x = l; x <= l + 1000 && x <= r; x++) {
        for(long long y = r; y >= r - 1000 && y >= x; y--) {
            if(__gcd(x, y) == 1) {
                result = max(result, y - x);
            }
        }
    }
    cout << result << '\n';
    return 0;
}
