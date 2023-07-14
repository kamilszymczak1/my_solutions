#include <iostream>

using namespace std;

void TestCase() {
    int a, b, c;
    cin >> a >> b >> c;
    int circleSize = abs(b - a) * 2;
    if(c > circleSize || a > circleSize || b > circleSize) {
        cout << - 1 << '\n';
    } else {
        cout << (c - 1 + circleSize / 2) % circleSize + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
