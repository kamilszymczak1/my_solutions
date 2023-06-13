#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const long long inf = 1ll << 60;

struct segment {
    int l, r;
    long long level;
    segment(int _l, int _r, int _level) : l(_l), r(_r), level(_level) {}
    int len() { return r - l + 1; }
};

bool operator< (segment a, segment b) {
    if(a.len() == b.len())
        return a.l < b.l;
    return a.len() > b.len();
}

struct segment_tree {
    vector<pair<long long, int>>values;
    int leaf_count;
    segment_tree(vector<long long>&a) {
        int n = a.size();
        for(leaf_count = 1; leaf_count < n; leaf_count *= 2) {}
        values.resize(leaf_count * 2);
        for(int i = 0; i < n; i++)
            values[i + leaf_count] = make_pair(a[i], i);
        for(int i = n; i < leaf_count; i++)
            values[i + leaf_count] = make_pair(inf, i);
        for(int i = leaf_count - 1; i > 0; i--)
            values[i] = min(values[i * 2], values[i * 2 + 1]);
    }
    void update(int x, long long new_value) {
        x += leaf_count;
        values[x] = make_pair(new_value, x - leaf_count);
        for(x /= 2; x > 0; x /= 2)
            values[x] = min(values[x * 2], values[x * 2 + 1]);
    }
    
    pair<long long, int>get_min(int l, int r) {
        l += leaf_count;
        r += leaf_count;
        pair<long long, int>result = min(values[l], values[r]);
        while(l / 2 != r / 2) {
            if(l % 2 == 0) {
                result = min(result, values[l + 1]);
            }
            if(r % 2 == 1) {
                result = min(result, values[r - 1]);
            }
            l /= 2;
            r /= 2;
        }
        return result;
    }
};

void test_case() {
    int n; cin >> n;
    vector<long long>a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = n - a[i];
    }
    long long m; cin >> m;
    
    set<segment>s;
    s.insert(segment(0, n - 1, 0));
    
    segment_tree t(a);
    
    long long result = 0;
    
    while(m > 0) {
        segment seg = *s.begin();
        s.erase(s.begin());
        
    //    cout << "l = " << seg.l << ", r = " << seg.r << '\n' << flush;
        
        vector<int>splits;
        pair<long long, int>p = t.get_min(seg.l, seg.r);
        long long lo = p.first;
        do {
           t.update(p.second, inf);
         //  cout << "p.second = " << p.second << '\n';
           splits.push_back(p.second);
           p = t.get_min(seg.l, seg.r);
        } while(p.first == lo);
        
        sort(splits.begin(), splits.end());
        
//         cout << "splits = ";
//         for(int x : splits)
//             cout << x << ' ';
//         cout << '\n' << flush;
        
        long long rows = lo - seg.level;
        
     //   cout << "rows = " << rows << '\n';
        
        if(m > rows * seg.len()) {
            result += (seg.len() - 1) * rows;
            m -= rows * seg.len();
        } else {
            result += (seg.len() - 1) * (m / seg.len());
            m %= seg.len();
            if(m > 0)
                result += m - 1;
            break;
        }
        
        if(splits[0] != seg.l) {
            s.insert(segment(seg.l, splits[0] - 1, lo));
        }
        
        if(splits.back() != seg.r) {
            s.insert(segment(splits.back() + 1, seg.r, lo));
        }
        
        for(int i = 0; i < (int)splits.size() - 1; i++) {
            if(splits[i] + 1 != splits[i + 1]) {
                s.insert(segment(splits[i] + 1, splits[i + 1] - 1, lo));
            }
        }
        
    }
    
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
