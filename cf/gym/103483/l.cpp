#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
    
using namespace std;
    
const int mod = 1'000'000'007;
const int inf = 1 << 30;
    
int add(int x, int y) { return (x + y) >= mod ? (x + y - mod) : (x + y); }
    
int others(vector<pair<int, int>>&pref) {
    int n = pref.size();
    vector<int>mod_sum(n), mod_cnt(n);
    int total_sum = 0, total_cnt = 0, answer = 0;
    for(auto &[x, y] : pref) {
        
        answer = (answer + 1ll * (total_cnt - mod_cnt[x]) * y - total_sum + mod_sum[x] + mod) % mod;
        
        mod_sum[x] = add(mod_sum[x], y);
        mod_cnt[x]++;
        total_sum = add(total_sum, y);
        total_cnt++;
    }
    return answer;
}
    
void compress(vector<pair<int, int>>&v) {
    vector<int>all;
    for(auto &[x, y] : v)
        all.push_back(x);
    sort(all.begin(), all.end());
    all.resize(unique(all.begin(), all.end()) - all.begin());
    for(auto &[x, y] : v)
        x = lower_bound(all.begin(), all.end(), x) - all.begin();
}
    
struct seg_tree {
    vector<int>values;
    int leaf_count;
    seg_tree(vector<int>&v) {
        int n = v.size();
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values.resize(leaf_count * 2, inf);
        for(int i = 0; i < n; i++)
            values[i + leaf_count] = v[i];
        for(int i = leaf_count - 1; i > 0; i--)
            values[i] = min(values[i * 2], values[i * 2 + 1]);
    }
    int get_min(int l, int r) {
        l += leaf_count;
        r += leaf_count;
        int answer = min(values[l], values[r]);
        while(l / 2 != r / 2) {
            if(l % 2 == 0)
                answer = min(answer, values[l + 1]);
            if(r % 2 == 1)
                answer = min(answer, values[r - 1]);
            l /= 2;
            r /= 2;
        }
        return answer;
    }
};
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int n, k; cin >> n >> k;
    vector<pair<int, int>>cards(n + 1);
    
    for(int i = 1; i <= n; i++) {
        cin >> cards[i].first >> cards[i].second;
        if(cards[i].first < cards[i].second)
            swap(cards[i].first, cards[i].second);
    }
    
    vector<pair<int, int>>pref(n + 1);
    for(int i = 1; i <= n; i++) {
        pref[i].first = (pref[i - 1].first + cards[i].first) % k;
        pref[i].second = (pref[i - 1].second + cards[i].first) % mod;
    }
    
    compress(pref);
    
    int answer = others(pref);
    
    vector<int>diff(n + 1, inf);
    for(int i = 1; i <= n; i++) {
        if(cards[i].first % k != cards[i].second % k) {
            diff[i] = cards[i].first - cards[i].second;
        }
    }
    
    seg_tree t(diff);
    
    vector<vector<int>>ind(n + 1);
    for(int i = 0; i <= n; i++)
        ind[pref[i].first].push_back(i);
    
    for(int i = 0; i <= n; i++) {
        if(ind[i].size() <= 1)
            continue;
        
        vector<pair<int, int>>values;
        for(int j = 1; j < (int)ind[i].size(); j++)
            values.emplace_back(t.get_min(ind[i][j - 1] + 1, ind[i][j]), j - 1);
        sort(values.begin(), values.end());
        
        vector<int>my_pref(ind[i].size());
        my_pref[0] = pref[ind[i][0]].second;
        for(int j = 1; j < (int)ind[i].size(); j++)
            my_pref[j] = add(my_pref[j - 1], pref[ind[i][j]].second);
        
        set<int>s;
        s.insert(0);
        s.insert((int)ind[i].size());
        
        for(auto [value, index] : values) {
            if(value == inf)
                break;
            auto it = s.upper_bound(index);
            int r = *it - 1;
            int l = *(--it);
            
            int left_cnt = index - l + 1;
            int right_cnt = r - index;
            
            int left_pref = my_pref[index] - (l == 0 ? 0 : my_pref[l - 1]);
            if(left_pref < 0)
                left_pref += mod;
            
            int right_pref = my_pref[r] - my_pref[index];
            if(right_pref < 0)
                right_pref += mod;
            
            int total_cnt = 1ll * left_cnt * right_cnt % mod;
            
            answer = (answer - 1ll * left_pref * right_cnt % mod + mod + 1ll * right_pref * left_cnt) % mod;
            
            answer = (answer - 1ll * total_cnt * value % mod + mod) % mod;
            
            s.insert(index + 1);
        }
    }
    
    cout << answer << '\n';
    
    return 0;
}
