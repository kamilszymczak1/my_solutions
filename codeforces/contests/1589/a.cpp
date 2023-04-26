#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        long long u, v; cin >> u >> v;
        cout << - u * u << ' ' << v * v << '\n';
    }
    return 0;
}
