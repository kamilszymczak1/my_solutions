#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        long long n, m; cin >> n >> m;
        cout << (n * m + 2) / 3 << '\n';
    }
    
    return 0;
}
