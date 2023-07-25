#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int inf = 1 << 30;

void TestCase() {
    int n, leftCnt = 0; cin >> n;
    vector<int>v(n, 0);
    for(auto &x : v) {
        cin >> x;
        if(x <= 0)
            leftCnt++;
    }
    sort(v.begin(), v.end());
    int minDiff = inf;
    for(int i = 1; i < n; i++) {
        if(v[i] <= 0) {
            minDiff = min(minDiff, v[i] - v[i - 1]);
        }
    }
    bool taken = false;
    for(int i = 0; i < n; i++) {
        if(v[i] > 0 && v[i] <= minDiff && !taken) {
            leftCnt++;
            taken = true;
        }
    }
    cout << leftCnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
}
