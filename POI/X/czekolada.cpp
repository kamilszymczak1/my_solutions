#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    vector<pair<int, bool>>v;
    int n, m, result = 0; cin >> n >> m;
    for(int i = 0; i < n + m - 2; i++) {
        int x; cin >> x;
        v.emplace_back(x, i < n - 1);
    }
    sort(v.begin(), v.end(), greater<pair<int, bool>>());
    vector<int>cuts(2, 0);
    for(auto [x, y] : v) {
        result += x * (cuts[y] + 1);
        cuts[y ^ 1]++;
    }
    cout << result << '\n';
    return 0;
}
