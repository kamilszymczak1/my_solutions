#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long ceil(long long x, long long y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

void TestCase() {
    long long hc, dc, hm, dm; cin >> hc >> dc >> hm >> dm;
    long long k, w, a; cin >> k >> w  >> a;
    bool result = false;
    for(long long x = 0; x <= k; x++) {
        long long L = ceil((hc + a * x), dm);
        long long R = dc + (k - x) * w;
        long double LL = L, RR = R;
        if(LL * RR >= (long double)hm)
            result = true;
        else if(L * R >= hm)
            result = true;
    }
    if(result)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
