#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, l; cin >> n >> l;
    vector<int>cntOne(l);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        for(int j = 0; j < l; j++) {
            cntOne[j] += x % 2;
            x /= 2;
        }
    }
    int result = 0;
    for(int i = l - 1; i >= 0; i--)
        result = result * 2 + (cntOne[i] * 2 > n);
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
