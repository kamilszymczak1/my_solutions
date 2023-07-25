#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<pair<int, int>>r;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        r.emplace_back(x, y);
    }
    for(int i = 1; i <= n; i++) {
        int k = -1;
        for(int j = 0; j < n; j++) {
            if(r[j].first <= i && i <= r[j].second) {
                if(k == -1 || r[k].second - r[k].first > r[j].second - r[j].first) {
                    k = j;
                }
            }
        }
        cout << r[k].first << ' ' << r[k].second << ' ' << i << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
