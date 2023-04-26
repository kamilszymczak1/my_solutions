#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, m; cin >> n >> m;
    int rb, cb; cin >> rb >> cb;
    int rd, cd; cin >> rd >> cd;
    
    int result = 1 << 30;
    if(rb <= rd) {
        result = min(result, rd - rb);
    } else {
        result = min(result, rb - rd + 2 * (n - rb));
    }
    if(cb <= cd) {
        result = min(result, cd - cb);
    } else {
        result = min(result, cb - cd + 2 * (m - cb));
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
