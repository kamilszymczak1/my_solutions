#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Interval {
    int l, r, id;
    Interval(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {}
};

bool operator< (Interval a, Interval b) {
    return a.l < b.l;
}

void test_case() {
    int n; scanf("%d", &n);
    vector<Interval>intervals;
    
    for(int i = 1; i <= n; i++) {
        int b; scanf("%d", &b);
        int lo, hi;
        if(b == 0) {
            lo = i + 1;
            hi = n;
        } else {
            lo = i / (b + 1) + 1;
            hi = i / b;
        }
        intervals.emplace_back(lo, hi, i);
    }
    sort(intervals.begin(), intervals.end());
    int k = 0;
    set<pair<int, int>>s;
    vector<int>a(n, -1);
    for(int i = 1; i <= n; i++) {
        while(k < n && intervals[k].l <= i) {
            s.insert(make_pair(intervals[k].r, intervals[k].id));
            k++;
        }
        auto [r, id] = *s.begin();
        s.erase(s.begin());
        a[id - 1] = i;
    }
    for(int x : a)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
