#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const bool BEG = 0, END = 1;

struct Point {
    int x, id;
    bool type;
    Point(int _x, int _id, int _type) : x(_x), id(_id), type(_type) {}
};

inline bool operator<(const Point &a, const Point &b) {
    if(a.x == b.x)
        return a.type < b.type;
    return a.x < b.x;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<Point>points;
    vector<vector<int>>next(n);
    for(int i = 0; i < m; i++) {
        int a, b, id; cin >> id >> a >> b;
        points.emplace_back(a, id - 1, BEG);
        points.emplace_back(b, id - 1, END);
    }
    sort(points.begin(), points.end());
    vector<int>occurenceCount(n, 0), result(n, 1), parent(n, -1), taken(n, false);
    
    set<int>s;
    for(Point p : points) {
        if(p.type == BEG) {
            occurenceCount[p.id]++;
            if(occurenceCount[p.id] == 1) {
                auto it = s.upper_bound(p.id);
                if(it != s.end())
                    next[p.id].push_back(*it);
                if(it != s.begin()) {
                    it--;
                    next[*it].push_back(p.id);
                }
                s.insert(p.id);
            }
        } else {
            occurenceCount[p.id]--;
            if(occurenceCount[p.id] == 0)
                s.erase(s.find(p.id));
        }
    }
    for(int i = n - 1; i >= 0; i--) {
        for(int y : next[i]) {
            if(result[y] + 1 > result[i]) {
                parent[i] = y;
                result[i] = result[y] + 1;
            }
        }
    }
    
    int maxInd = max_element(result.begin(), result.end()) - result.begin();
    cout << n - result[maxInd] << '\n';
    for(int i = 0; i < n; i++) {
        if(i == maxInd) {
            maxInd = parent[maxInd];
        } else {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
    
}
