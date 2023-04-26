#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, m; cin >> n >> m;
    vector<int>X(n);
    for(auto &x : X)
        cin >> x;
    vector<string>S(n);
    for(auto &s : S)
        cin >> s;
    
    int result = 0, bestMask = 0;
    for(int mask = 0; mask < (1 << n); mask++) {
        int localResult = 0;
        for(int i = 0; i < n; i++) {
            localResult += X[i] * ((((1 << i) & mask) > 0) > 0 ? -1 : 1);
        }
        vector<int>weight(m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                weight[j] += (S[i][j] == '1') * ((((1 << i) & mask) > 0) > 0 ? 1 : -1);
            }
        }
        sort(weight.begin(), weight.end());
        for(int i = 1; i <= m; i++)
            localResult += weight[i - 1] * i;
        
        if(localResult > result) {
            bestMask = mask;
            result = localResult;
        }
    }
    
    vector<int>p(m);
    vector<pair<int, int>>weight(m);
    for(int i = 0; i < m; i++)
        weight[i].second = i;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            weight[j].first += (S[i][j] == '1') * ((((1 << i) & bestMask) > 0) > 0 ? 1 : -1);
        }
    }
    sort(weight.begin(), weight.end());
    for(int i = 0; i < m; i++)
        p[weight[i].second] = i + 1;
    for(int x : p)
        cout << x << ' ';
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
