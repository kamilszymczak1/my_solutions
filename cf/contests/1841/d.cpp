#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 30;

void test_case() {
    int n; cin >> n;
    vector<pair<int, int>>segments(n);
    vector<int>ends;
    for(auto &[x, y] : segments) {
        cin >> x >> y;
        ends.push_back(y);
    }
    sort(ends.begin(), ends.end());
    sort(segments.begin(), segments.end());
    ends.erase(unique(ends.begin(), ends.end()), ends.end());
    
    vector<int>dp(ends.size() + 1);
    
    for(int i = 0; i < n; i++) {
        int l = segments[i].first;
        int r = segments[i].second;
        int max_r = inf;
        for(int j = i + 1; j < n; j++) {
            if(segments[j].first <= segments[i].second) {
                max_r = min(max_r, max(r, segments[j].second));
            }
        }
        if(max_r == inf)
            continue;
        int my_dp_value = 0;
        for(int j = 0; j < n && ends[j] < l; j++) {
            my_dp_value = max(my_dp_value, dp[j]);
        }
        int my_ind = lower_bound(ends.begin(), ends.end(), max_r) - ends.begin();
        
        dp[my_ind] = max(dp[my_ind], my_dp_value + 2);
        
    }
    
    int result = n;
    for(int i = 0; i < dp.size(); i++)
        result = min(result, n - dp[i]);
    
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
