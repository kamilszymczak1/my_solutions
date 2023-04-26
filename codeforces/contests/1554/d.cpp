#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    int k = n / 2;
    string middle = (n % 2 == 0 || n == 1) ? "b" : "bc";
    cout << string(k, 'a') + middle + string(max(0, k - 1), 'a') << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
