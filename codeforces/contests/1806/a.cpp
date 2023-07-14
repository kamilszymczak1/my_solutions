#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
#include <queue>
#include <set>
#include <map>

using namespace std;

void test_case() {
    long long a, b, c, d; cin >> a >> b >> c >> d;
    
    if(b > d) {
        cout << "-1\n";
        return;
    }
    
    long long moves1 = d - b;
    
    a += moves1;
    b += moves1;
    
    if(a < c) {
        cout << "-1\n";
        return;
    }
    
    long long moves2 = a - c;
    
    cout << moves1 + moves2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
