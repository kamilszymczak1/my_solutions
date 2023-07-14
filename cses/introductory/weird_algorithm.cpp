#include <iostream>

using namespace std;

int main() {
    long long x; cin >> x;
    while(x != 1) {
        cout << x << ' ';
        x = x % 2 == 0 ? x / 2 : 3 * x + 1;
    }
    cout << "1\n";
    return 0;
}
