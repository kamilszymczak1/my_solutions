#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <bitset>

using namespace std;

const int inf = 1 << 30;

bool pair_cmp(pair<int, int>a, pair<int, int>b) {
    if(a.first == b.first)
        return a.second > b.second;
    return a.first < b.first;
}

int get(vector<pair<int, int>>v) {
    int n = v.size();
    sort(v.begin(), v.end(), pair_cmp);
    multiset<int>b;
    for(auto &[x, y] : v)
        b.insert(y);
    int b_suff_max = -1;
    int answer = inf;
    for(int i = n - 1; i >= 0; i--) {
        b.erase(b.find(v[i].second));
        
        if(b_suff_max <= v[i].first) {
            if(i != n - 1)
                answer = min(answer, v[i].first - b_suff_max);
            if(!b.empty()) {
                auto it = b.upper_bound(v[i].first);
                if(it != b.begin()) {
                    it--;
                    answer = min(answer, v[i].first - *it);
                }
            }
        }
        
        b_suff_max = max(b_suff_max, v[i].second);
    }
    return answer;
}

void test_case() {
    int n; cin >> n;
    vector<pair<int, int>>v;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        v.emplace_back(x, y);
    }
    int answer = get(v);
    for(auto &[x, y] : v)
        swap(x, y);
    answer = min(answer, get(v));
    cout << answer << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
