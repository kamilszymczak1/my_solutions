#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n, m; cin >> n >> m;
    if(m == 1) {
        cout << "YES\n";
        for(int i = 0; i < n; i++)
            cout << i + 1 << '\n';
        return;
    }
    int even = n * m / 2;
    int odd = n * m - even;
    if(n % 2 != 0 || even != odd) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<vector<int>>ans(n, vector<int>(m, 0));
    int j = 0;
    for(int i = 0; i < n / 2; i++) {
        for(int k = 0; k < m; k++) {
            ans[2 * i][k] = ++j;
            ans[2 * i + 1][k] = ++j;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < m; k++) {
            cout << ans[i][k] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
