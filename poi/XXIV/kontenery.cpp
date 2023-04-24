#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    
    const int T = sqrt(n / 2.0) + 1;
    
    vector<int>ans(n);
    
    vector<vector<pair<int, int>>>toAdd(n); //d and lastIndex
    
    while(k--) {
        int a, l, d; cin >> a >> l >> d; a--;
        if(d >= T || l < T) {
            for(int i = 0; i < l; i++)
                ans[a + i * d]++;
        } else {
            int lastIndex = a + l * d;
            toAdd[a].emplace_back(d, lastIndex);
        }
    }
    
    for(int i = 0; i < n; i++)
        sort(toAdd[i].begin(), toAdd[i].end());
    
    vector<int>index(n, 0), toPropagate(n + T + 1);
    for(int d = 1; d < T; d++) {
        for(int i = 0; i < n; i++) {
            while(index[i] < toAdd[i].size() && toAdd[i][index[i]].first == d) {
                toPropagate[i] += 1;
                toPropagate[toAdd[i][index[i]].second]--;
                index[i]++;
            }
            ans[i] += toPropagate[i];
            toPropagate[i + d] += toPropagate[i];
            toPropagate[i] = 0;
        }
    }
    
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
