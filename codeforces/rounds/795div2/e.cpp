#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Segment {
    int c, l, r;
    Segment(int _c, int _l, int _r) : c(_c), l(_l), r(_r) {}
};

bool operator< (Segment a, Segment b) {
    if(a.r == b.r)
        return a.l < b.l;
    return a.r < b.r;
}

void test_case() {
    int n; scanf("%d", &n);
    vector<Segment>s;
    for(int i = 0; i < n; i++) {
        int c, l, r; scanf("%d%d%d", &c, &l, &r);
        s.emplace_back(c, l, r);
    }
    sort(s.begin(), s.end());
    multiset<pair<int, int>>o[2];
    for(auto [c, l, r] : s) {
        int my_r = -1;
        for(auto it = o[c ^ 1].end(); it != o[c ^ 1].begin(); it = o[c ^ 1].end()) {
            it--;
            if(it -> first < l)
                break;
            o[c].erase(o[c].find(make_pair(it -> second, it -> first)));
            my_r = max(my_r, it -> first);
            o[c ^ 1].erase(it);
        }
        
        o[c].insert(make_pair(r, my_r));
        o[c ^ 1].insert(make_pair(my_r, r));
    }
    
    printf("%d\n", (int)o[0].size());
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
