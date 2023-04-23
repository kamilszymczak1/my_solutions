#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

#define LSB(x) (x & (-x))

const int MAX_Y = 200007;

struct Event {
    int x, y, id;
    bool beg;
    Event(int _x, int _y) : x(_x), y(_y), id(-1) {}
    Event(int _x, int _y, int _id, bool _beg) : x(_x), y(_y), id(_id), beg(_beg) {}
};

bool cmp(Event &a, Event &b) {
    if(a.x == b.x) {
        return a.id < b.id;
    }
    return a.x < b.x;
}

struct RangeQueries {
    vector<int>values;
    RangeQueries(int _size) {
        values.resize(_size + 7);
    }
    void Add(int x, int value) {
        for(x++; x < values.size(); x += LSB(x))
            values[x] += value;
    }
    int PrefixSum(int x) {
        int result = 0;
        for(; x > 0; x -= LSB(x))
            result += values[x];
        return result;
    }
    int Sum(int a, int b) {
        return PrefixSum(b + 1) - PrefixSum(a);
    }
};

void Calculate(vector<pair<int, int>>&points, vector<int>&ans, vector<pair<int, int>>&queries, vector<int>&cnt) {
    vector<Event>events;
    for(auto [x, y] : points) {
        events.emplace_back(x, y);
    }
    for(int i = 0; i < queries.size(); i++) {
        events.emplace_back(queries[i].first - ans[i] - 1, queries[i].second, i, true);
        events.emplace_back(queries[i].first + ans[i], queries[i].second, i, false);
    }
    sort(events.begin(), events.end(), cmp);
    RangeQueries r(MAX_Y);
    for(Event &e : events) {
        if(e.id == -1) {
            r.Add(e.y, 1);
        } else {
            if(e.beg) {
                cnt[e.id] = -r.Sum(max(-1, e.y - ans[e.id]), min(MAX_Y, e.y + ans[e.id]));
            } else {
                cnt[e.id] += r.Sum(max(-1, e.y - ans[e.id]), min(MAX_Y, e.y + ans[e.id]));
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>>points;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.emplace_back(x - y, x + y);
    }
    int q; cin >> q;
    vector<int>k(q), ans(q, (1 << 20) - 1), cnt(q);
    vector<pair<int, int>>queries;
    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y >> k[i];
        queries.emplace_back(x - y, x + y);
    }
    
    for(int i = 19; i >= 0; i--) {
        for(int j = 0; j < q; j++)
            ans[j] -= 1 << i;
        Calculate(points, ans, queries, cnt);
        for(int j = 0; j < q; j++) {
            if(cnt[j] < k[j]) {
                ans[j] += 1 << i;
            }
        }
    }
    
    for(int i = 0; i < q; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    
    return 0;
}
