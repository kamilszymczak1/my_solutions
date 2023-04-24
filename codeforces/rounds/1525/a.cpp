#include <iostream>

using namespace std;

void TestCase() {
    int k;
    cin >> k;
    int a = k, b = 100 - k;
    
    for(int i = 2; i <= 100; i++) {
        while(a % i == 0 && b % i == 0) {
            a /= i;
            b /= i;
        }
    }
    cout << a + b << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        TestCase();
    }
    return 0;
}
