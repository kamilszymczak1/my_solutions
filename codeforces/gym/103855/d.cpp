#include <cstdio>
#include <vector>
#include <set>
 
using namespace std;
 
struct Point {
    int x, y, v;
    Point() : x(0), y(0), v(0) {}
    Point(int _x, int _y, int _v) : x(_x), y(_y), v(_v) {}
};
 
int Solve(vector<Point>p) {
    vector<int>xCount(1'000'001), yCount(1'000'001);
    vector<vector<Point>>ys(1'000'001);
    for(Point t : p) {
        xCount[t.x] += t.v;
        yCount[t.y] += t.v;
        ys[t.y].emplace_back(t);
    }
    set<pair<int, int>>bestX;
    for(int i = 0; i <= 1'000'000; i++)
        bestX.insert(make_pair(-xCount[i], i));
    
    
    auto it = bestX.begin();
    int result = 0;
    for(int i = 0; i < 3; i++) {
        result += - it -> first;
        it++;
    }
    
    for(int y = 0; y <= 1'000'000; y++) {
        for(Point t : ys[y]) {
            bestX.erase(bestX.find(make_pair(-xCount[t.x], t.x)));
            xCount[t.x] -= t.v;
            bestX.insert(make_pair(-xCount[t.x], t.x));
        }
        
        int local = 0;
        it = bestX.begin();
        for(int i = 0; i < 2; i++) {
            local += - it -> first;
            it++;
        }
        result = max(result, local + yCount[y]);
        
        for(Point t : ys[y]) {
            bestX.erase(bestX.find(make_pair(-xCount[t.x], t.x)));
            xCount[t.x] += t.v;
            bestX.insert(make_pair(-xCount[t.x], t.x));
        }
    }
    return result;
}
