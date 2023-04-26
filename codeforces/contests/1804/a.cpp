#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>

using namespace std;

void test_case() {
    int a, b; cin >> a >> b;
    a = abs(a);
    b = abs(b);
    
    int diff = abs(a - b);
    
    if(a == b) {
        cout << max(a, b) * 2 << '\n';
    } else {
        cout << max(a, b) * 2 - 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
