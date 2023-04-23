#include <iostream>
#include <vector>

using namespace std;

int Calc(int x, int pos) {
    if(x & (1 << pos)) {
        int right = 1 << pos;
        int left = (x >> (pos + 1)) + 1;
        return right * left;
    } else {
        int right = 1 << pos;
        int left = (x >> (pos + 1));
        int result = right * left;
        right = (x & ((1 << pos) - 1)) + 1;
        return result + right;
    }
}

void TestCase() {
    int l, r; cin >> l >> r;
    int result = 1 << 30;
    for(int i = 0; (1 << i) <= r; i++) {
        result = min(result, Calc(r, i) - Calc(l - 1, i));
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
