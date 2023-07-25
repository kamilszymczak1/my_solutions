#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    long long n, x, y; cin >> n >> x >> y;
    for(int i = 0; i < n; i++) {
        long long a; cin >> a;
        x += a;
    }
    if(x % 2 == y % 2) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
