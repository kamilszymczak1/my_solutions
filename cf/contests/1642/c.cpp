#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

void TestCase() {
    int n, x; cin >> n >> x;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    map<int, int>cnt;
    for(int i = 0; i < n; i++) {
        if(a[i] % x == 0) {
            int b = a[i] / x;
            if(cnt[b] > 0) {
                cnt[b]--;
            } else {
                cnt[a[i]]++;
            }
        } else {
            cnt[a[i]]++;
        }
    }
    int result = 0;
    for(auto [val, c] : cnt)
        result += c;
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
