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
    int n; cin >> n;
    int zero_count = 0, one_count = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        zero_count += (x == 0);
        one_count += (x == 1);
    }
    
    if((n % 2 == 0 && zero_count <= n / 2) || (n % 2 == 1 && zero_count <= n / 2 + 1)) {
        cout << "0\n";
        return;
    }
    
    if(one_count + zero_count == n && zero_count != n) {
        cout << "2\n";
    } else{
        cout << "1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
