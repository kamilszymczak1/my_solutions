#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    const int MAX_N = 150000;
    vector<int>a(n);
    vector<vector<int>>pos(MAX_N);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; a[i]--;
        pos[a[i]].push_back(i);
    }
    int result = -1;
    for(vector<int>&v : pos) {
        for(int i = 0; i < (int)v.size() - 1; i++) {
            int A = v[i], B = v[i + 1];
            int leftMax = A - 1;
            int rightMax = n - B;
            result = max(result, leftMax + rightMax + 1);
        }
    }
    cout << result << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
