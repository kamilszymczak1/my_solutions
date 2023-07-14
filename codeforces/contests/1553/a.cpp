#include <iostream>

using namespace std;

void TestCase() {
    int n; cin >> n;
    cout << n / 10 + (n % 10 == 9) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
