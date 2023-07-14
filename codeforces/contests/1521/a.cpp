#include <iostream>

using namespace std;

void TestCase() {
    long long A, B;
    cin >> A >> B;
    if(B == 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    if(B == 2) {
        cout << A * 3 << ' ' << A << ' ' << A * B * 2 << '\n';
    } else {
        cout << A * (B - 1) << ' ' << A << ' ' << A * B << '\n';
    }
    
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
