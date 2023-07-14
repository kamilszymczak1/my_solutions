#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    long long x, y; cin >> x;
    long long result = 0;
    for(int i = 1; i < n; i++) {
        cin >> y;
        result = max(result, x * y);
        x = y;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
