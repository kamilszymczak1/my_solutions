#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
    }
    vector<int>v = {1, 2, 1, 1, 2, 1};
    cout << 3 * n << '\n';
    for(int i = 0; i < n; i += 2) {
        for(auto x : v)
            cout << x << ' ' << i + 1 << ' ' << i + 2 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
