#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

void test_case() {
    int n, x, p; cin >> n >> x >> p;
    for(int i = 1; i <= min(2 * n + 1, p); i++) {
        long long y = 1ll * i * (i + 1) / 2;
        if((x + y) % n == 0) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
