#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int>v(n);
    for(auto &x : v)
        cin >> x;
    sort(v.begin(), v.end(), greater<int>());
    for(k--; k < n && v[k] == v[k + 1]; k++) {}
    cout << k + 1 << '\n';
    return 0;
}
