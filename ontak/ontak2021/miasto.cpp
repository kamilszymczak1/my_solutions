#include <iostream>
#include <vector>
#include <map>

using namespace std;

constexpr int TRANSLATE = 2000007;

struct SegTree {
    vector<int>value;
    int leafCount;
    SegTree(int _n) {
        for(int leafCount = 1; leafCount < _n; leafCount <<= 1) {}
        value.reserve(leafCount << 1);
        value.resize(leafCount << 1, 0);
    };
    void AddOne(int x) {
        for(x += leafCount; x; x >>= 1)
            value[x]++;
    }
    int Sum(int a, int b) {
        a += leafCount;
        b += leafCount;
        int result = value[a];
        if(a != b)
            result += value[b];
        for(; (a / 2) != (b / 2); a /= 2, b /= 2) {
            if(a % 2 == 0) {
                result += value[a];
            }
            if(b % 2 == 1) {
                result += value[b];
            }
        }
        return result;
    }
};

struct Point {
    int x, y;
    bool good;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y), good(true) {}
};

bool operator< (const Point a, const Point b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmpNE()

void Solve(vector<Point>&points, map<Point, bool>&taken) {
    //ne
    vector<Point>ne = points, se = points, sw = points, nw = points;
    
    
}

int main() {
    ios_base::sync_with_stdio(0);
    
    vector<Point>points;
    map<Point, bool>taken;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.emplace_back(x, y);
        taken[{x, y}] = true;
    }
    
    return 0;
}
