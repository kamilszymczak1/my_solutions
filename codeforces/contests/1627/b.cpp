#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void TestCase() {
    int n, m; cin >> n >> m;
    multiset<int>s;
    vector<int>v;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int dx = max(i - 1, (int)abs(n - i));
            int dy = max(j - 1, (int)abs(m - j));
            v.emplace_back(dx + dy);
        }
    }
    sort(v.begin(), v.end());
    for(int i = 0; i < n * m; i++)
        cout << v[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
