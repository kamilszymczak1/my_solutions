#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <bitset>

using namespace std;

struct segment_tree {
    vector<int>values;
    int leaf_count;
    segment_tree(int n) {
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values.resize(leaf_count * 2);
    }
    int max_prefix(int x) {
        x += leaf_count;
        int answer = values[x];
        while(x > 1) {
            if(x % 2 == 1) {
                answer = max(answer, values[x - 1]);
            }
            x /= 2;
        }
        return answer;
    }
    void update(int x, int value) {
        x += leaf_count;
        values[x] = max(values[x], value);
        for(x /= 2; x > 1; x /= 2)
            values[x] = max(values[x * 2], values[x * 2 + 1]);
    }
};

int scale(vector<vector<int>>&v) {
    vector<int>all;
    for(auto &vec : v) {
        for(auto &x : vec) {
            all.emplace_back(x);
        }
    }
    sort(all.begin(), all.end());
    for(auto &vec : v) {
        for(auto &x : vec) {
            x = lower_bound(all.begin(), all.end(), x) - all.begin() + 1;
        }
    }
    
    return all.size() + 1;
}

void test_case() {
    int n; cin >> n;
    vector<vector<int>>v(n);
    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        for(int j = 0; j < k; j++) {
            int x; cin >> x;
            if(v[i].empty() || x > v[i].back())
                v[i].emplace_back(x);
        }
    }
    int hi = scale(v);
    
    segment_tree t(hi);
    
    vector<pair<int, int>>ord;
    for(int i = 0; i < n; i++)
        ord.emplace_back(v[i].back(), i);
    sort(ord.begin(), ord.end());
    for(auto [xx, i] : ord) {
        int k = v[i].size();
        int my_dp = 0;
        for(int j = 0; j < k; j++) {
            my_dp = max(my_dp, t.max_prefix(v[i][j] - 1) + k - j);
        }
        t.update(v[i].back(), my_dp);
    }
    cout << t.max_prefix(hi - 1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}

