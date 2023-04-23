#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int a, b; cin >> a >> b;
    cout << max(0, b - a + 1) << '\n';
    
    return 0;
}
