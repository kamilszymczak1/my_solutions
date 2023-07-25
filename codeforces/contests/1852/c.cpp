#include <iostream>
#include <vector>
#include <set>
    
using namespace std;
    
const long long inf = 1ll << 60;

struct segtree {
    vector<long long>values;
    int leaf_count;
    segtree(vector<long long>&v) {
        int n = v.size();
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values.resize(leaf_count * 2);
        for(int i = 0; i < n; i++)
            values[i + leaf_count] = v[i];
    }
    void add_range(int l, int r, long long value) { 
        l += leaf_count;
        r += leaf_count;
        values[l] += value;
        if(l != r)
            values[r] += value;
        while(l / 2 != r / 2) {
            if(l % 2 == 0)
                values[l + 1] += value;
            if(r % 2 == 1)
                values[r - 1] += value;
            l /= 2;
            r /= 2;
        }
    }
    long long get(int x) {
        long long result = 0;
        for(x += leaf_count; x > 0; x /= 2)
            result += values[x];
        return result;
    }
};
    
void test_case() {
    int n; cin >> n;
    long long k; cin >> k;
    
    vector<long long>a(n);
    for(auto &x : a) {
        cin >> x;
        if(x == k)
            x = 0;
    }
    
    segtree t(a);
    
    set<pair<long long, int>>s;
    for(int i = 1; i < n; i++) {
        if(t.get(i - 1) < t.get(i) && !s.empty()) {
            auto p = *s.begin();
            if(p.first < t.get(i) - t.get(i - 1)) {
                t.add_range(p.second, i - 1, k);
                s.erase(s.begin());
            }
        }
        
        if(t.get(i - 1) >= t.get(i)) {
            long long diff = t.get(i - 1) - t.get(i);
            t.add_range(i, i, k * (diff / k));
            s.insert(make_pair(t.get(i) + k - t.get(i - 1), i));
        }
    }
    
    long long result = t.get(0);
    for(int i = 1; i < n; i++)
        result += max(0ll, t.get(i) - t.get(i - 1));
    cout << result << '\n';
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
