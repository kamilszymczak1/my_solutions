#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int>v(n, 0);
        for(auto &x : v)
            cin >> x;
        sort(v.begin(), v.end());
        int i = 0;
        while(i < v.size() - 1 && v[i] == v[i + 1])
            i++;
        cout << n - i - 1 << '\n';
    }
}
