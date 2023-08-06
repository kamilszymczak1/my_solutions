#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

long long query(int l, int r) {
    if(l == r)
        return 0;
    cout << "? " << l << ' ' << r << '\n' << flush;
    long long x; cin >> x;
    return x;
}

int go(int l, int r) {
    if(l == r)
        return l;
    int mid = (l + r) / 2;
    
    int x = go(l, mid);
    int y = go(mid + 1, r);
    
    if(query(x, y - 1) == query(x, y))
        return y;
    return x;
}

void test_case() {
    int n; cin >> n;
    int result = go(1, n);
    cout << "! " << result << '\n' << flush;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
