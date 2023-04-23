#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int trans = 200'007;
const int SIZE = 400'007;
const vector<pair<int, int>>moves = {{0, 2}, {1, 1}, {2, 0}};

#define x first
#define y second

pair<int, int>Check(pair<int, int>&point, int d, vector<vector<int>>&r, vector<vector<int>>&c) {
    auto it1 = lower_bound(c[point.x - d].begin(), c[point.x - d].end(), point.y - d);
    auto it2 = upper_bound(c[point.x - d].begin(), c[point.x - d].end(), point.y + d);
    if(it2 - it1 < d + 1) {
        if(it1 == c[point.x - d].end() || *it1 > point.y - d) {
            return make_pair(point.x - d, point.y - d);
        }
        int ind = it1 - c[point.x - d].begin();
        while(ind < (int)c[point.x - d].size() - 1 && c[point.x - d][ind] == c[point.x - d][ind + 1] - 2)
            ind++;
        return make_pair(point.x - d, c[point.x - d][ind] + 2);
    }
    it1 = lower_bound(c[point.x + d].begin(), c[point.x + d].end(), point.y - d);
    it2 = upper_bound(c[point.x + d].begin(), c[point.x + d].end(), point.y + d);
    if(it2 - it1 < d + 1) {
        if(it1 == c[point.x + d].end() || *it1 > point.y - d) {
            return make_pair(point.x + d, point.y - d);
        }
        int ind = it1 - c[point.x + d].begin();
        while(ind < (int)c[point.x + d].size() - 1 && c[point.x + d][ind] == c[point.x + d][ind + 1] - 2)
            ind++;
        return make_pair(point.x + d, c[point.x + d][ind] + 2);
    }
    it1 = lower_bound(r[point.y - d].begin(), r[point.y - d].end(), point.x - d);
    it2 = upper_bound(r[point.y - d].begin(), r[point.y - d].end(), point.x + d);
    if(it2 - it1 < d + 1) {
        if(it1 == r[point.y - d].end() || *it1 > point.x - d) {
            return make_pair(point.x - d, point.y - d);
        }
        int ind = it1 - r[point.y - d].begin();
        while(ind < (int)r[point.y - d].size() - 1 && r[point.y - d][ind] == r[point.y - d][ind + 1] - 2)
            ind++;
        return make_pair(r[point.y - d][ind] + 2, point.y - d);
    }
    it1 = lower_bound(r[point.y + d].begin(), r[point.y + d].end(), point.x - d);
    it2 = upper_bound(r[point.y + d].begin(), r[point.y + d].end(), point.x + d);
    if(it2 - it1 < d + 1) {
        if(it1 == r[point.y + d].end() || *it1 > point.x - d) {
            return make_pair(point.x - d, point.y + d);
        }
        int ind = it1 - r[point.y + d].begin();
        while(ind < (int)r[point.y + d].size() - 1 && r[point.y + d][ind] == r[point.y + d][ind + 1] - 2)
            ind++;
        return make_pair(r[point.y + d][ind] + 2, point.y + d);
    }
    return make_pair(-trans, -trans);
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<pair<pair<int, int>, int>>p;
    vector<vector<int>>r(SIZE), c(SIZE);
    map<pair<int, int>, int>m;
    for(int i = 0; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        p.emplace_back(make_pair(x - y + trans, x + y), i);
        m[p.back().first] = i;
        r[x + y].emplace_back(x - y + trans);
        c[x - y + trans].emplace_back(x + y);
    }
    
    for(int i = 0; i < SIZE; i++) {
        sort(r[i].begin(), r[i].end());
        sort(c[i].begin(), c[i].end());
    }
    
    sort(p.begin(), p.end());
    vector<pair<int, int>>ans(n);
    vector<int>d(n);
    for(pair<pair<int, int>, int>P : p) {
        int id = P.second;
        pair<int, int>best, point = P.first;
        do {
            d[id]++;
            best = Check(point, d[id], r, c);
        } while(best.y == -trans);
        for(pair<int, int>move : moves) {
            pair<int, int>newPoint = make_pair(point.x + move.x, point.y + move.y);
            if(m.find(newPoint) != m.end()) {
                int sub = max(move.x, move.y) == 2 ? 3 : 2;
                d[m[newPoint]] = max(d[m[newPoint]], d[id] - sub);
            }
        }
        best.x -= trans;
        ans[id] = make_pair((best.x + best.y) / 2, (best.y - best.x) / 2);
    }
    for(auto P : ans)
        printf("%d %d\n", P.first, P.second);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
