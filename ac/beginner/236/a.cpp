#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, x = 0; cin >> n;
    for(int i = 0; i < 4 * n - 1; i++) {
        int a; cin >> a;
        x ^= a;
    }
    cout << x << '\n';
    
    
    return 0;
}
