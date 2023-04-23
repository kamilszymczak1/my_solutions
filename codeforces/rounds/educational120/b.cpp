#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>p(n);
    for(int &x : p) {
        cin >> x; x--;
    }
    string s; cin >> s;
    vector<pair<int, int>>onePositions, zeroPositions;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            zeroPositions.emplace_back(p[i], i);
        } else {
            onePositions.emplace_back(p[i], i);
        }
    }
    sort(zeroPositions.begin(), zeroPositions.end(), greater<pair<int, int>>());
    sort(onePositions.begin(), onePositions.end(), greater<pair<int, int>>());
    vector<int>ans(n);
    int value = n;
    for(int i = 0; i < onePositions.size(); i++)
        ans[onePositions[i].second] = value--;
    for(int i = 0; i < zeroPositions.size(); i++)
        ans[zeroPositions[i].second] = value--;
    
    for(int x : ans) {
        cout << x << ' ';
    }
    cout << '\n';
}


int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--) {
        TestCase();
    }
    
    return 0;
}
