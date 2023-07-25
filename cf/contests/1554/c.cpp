#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

bool IsBitSet(int x, int bit) {
    return x & (1 << bit);
}

void TestCase() {
    int n, m; cin >> n >> m; m++;
    int result = 0, smaller = false;
    for(int i = 29; i >= 0 && !smaller; i--) {
        if(IsBitSet(m, i) && !IsBitSet(n, i))
            result |= 1 << i;
        if(!IsBitSet(m, i) && IsBitSet(n, i))
            smaller = true;
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
