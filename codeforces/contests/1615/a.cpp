#include <iostream>

using namespace std;

void TestCase() {
    int n; cin >> n;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        sum += x;
    }
    if(sum % n == 0) {
        cout << "0\n";
    } else {
        cout << "1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    
    
    return 0;
}
