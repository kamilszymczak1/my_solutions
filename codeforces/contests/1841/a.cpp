#include <iostream>

using namespace std;

void test_case() {
    int n; cin >> n;
    cout << (n >= 5 ? "Alice" : "Bob") << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
