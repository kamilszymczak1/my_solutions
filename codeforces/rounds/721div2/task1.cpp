#include <iostream>

using namespace std;

void TestCase() {
    long long n;
    cin >> n;
    if(n == 2) {
        cout << 1 << '\n';
        return;
    }
    if(n == 1) {
        cout << 0 << '\n';
        return;
    }
    int k = 1;
    while(k * 2 <= n)
        k = k * 2;
    
    cout << k - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
