#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct SegTree {
    vector<long long>values;
    int leafCount;
    SegTree(int _n) {
        for(leafCount = 1; leafCount < _n; leafCount *= 2) {}
        values.resize(leafCount * 2);
    }
    void Add(int a, int b, long long x) {
        a += leafCount; b += leafCount;
        values[a] += x;
        if(a != b)
            values[b] += x;
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                values[a + 1] += x;
            if(b % 2 == 1)
                values[b - 1] += x;
            a /= 2; b /= 2;
        }
    }
    long long Query(int x) {
        long long result = 0;
        for(x += leafCount; x; x /= 2)
            result += values[x];
        return result;
    }
};

struct Interval {
    int a, b, c;
    Interval(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
};

bool operator<(Interval a, Interval b) {
    return a.a < b.a;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    set<Interval>colours;
    colours.insert(Interval(0, n - 1, 1));
    SegTree T(n);
    map<int, long long>colourOffset;
    while(q--) {
        string s; cin >> s;
        if(s[0] == 'C') { //colour
            int l, r, c; cin >> l >> r >> c; l--; r--;
            auto it = colours.upper_bound(Interval(l, r, 0)); it--;
            if(it -> b >= l) {
                T.Add(l, min(it -> b, r), colourOffset[it -> c]);
                int a = it -> a, b = it -> b, c = it -> c;
                auto toErase = it; it++;
                colours.erase(toErase);
                if(a <= l - 1) {
                    colours.insert(Interval(a, l - 1, c));
                }
                if(b > r) {
                    colours.insert(Interval(r + 1, b, c));
                }
            }
            while(it != colours.end() && it -> b <= r) {
                T.Add(it -> a, it -> b, colourOffset[it -> c]);
                auto toErase = it; it++;
                colours.erase(toErase);
            }
            if(it != colours.end() && it -> a <= r) {
                T.Add(it -> a, r, colourOffset[it -> c]);
                int a = it -> a, b = it -> b, c = it -> c;
                auto toErase = it; it++;
                colours.erase(toErase);
                colours.insert(Interval(r + 1, b, c));
            }
            colours.insert(Interval(l, r, c));
            T.Add(l, r, -colourOffset[c]);
        } else if(s[0] == 'A') {
            int c; cin >> c; long long x; cin >> x;
            colourOffset[c] += x;
        } else {
            int x; cin >> x; x--;
            auto it = colours.upper_bound(Interval(x, 0, 0)); it--;
            int c = it -> c;
            cout << T.Query(x) + colourOffset[c] << '\n';
        }
    }
    
    
    return 0;
}
