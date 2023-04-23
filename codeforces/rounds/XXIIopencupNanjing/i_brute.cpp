#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
    
using namespace std;
    
const int BOARD = 0, COIN = 1;
    
struct Point {
    int x, y, type, id;
    Point() {}
    Point(int _x, int _y, int _type) : x(_x), y(_y), type(_type) {}
};
    
bool operator< (Point a, Point b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}
    
bool operator== (Point a, Point b) {
    return a.id == b.id;
}
    
int mod(long long a, int b) {
    if(a >= 0)
        return a % b;
    a = (-a) % b;
    return a == 0 ? 0 : (b - a);
}
    
void TestCase() {
    int h; scanf("%d", &h);
    vector<Point>points;
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        points.emplace_back(x, y, BOARD);
    }
    int m; scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        points.emplace_back(x, y, COIN);
    }
    sort(points.begin(), points.end());
    for(int i = 0; i < (int)points.size(); i++)
        points[i].id = i;
    map<int, vector<Point>>m1, m2; //m1 for y = x + b, m2 for y = -x + b
    for(Point p : points) {
        m1[p.y - p.x].emplace_back(p);
        m2[p.y + p.x].emplace_back(p);
    }
    
    vector<int>dpUp(n + m), dpDown(n + m);
    reverse(points.begin(), points.end());
    
    map<long long, int>l1, l2; //l1 for y = x + b, m2 for y = -x + b
    
    for(Point p : points) {
        //Calculate dpUp
        
        auto myLine = &m1[p.y - p.x];
        if(p == myLine -> back()) {
            
            if(l1.find(mod(p.y - p.x, 2 * h)) != l1.end()) {
                long long x = l1[mod(p.y - p.x, 2 * h)];
                dpUp[p.id] = max(dpUp[p.id], dpUp[m1[x].begin() -> id]);
            }
            
            if(l2.find(mod(2ll * h - p.y + p.x, 2 * h)) != l2.end()) {
                long long x = l2[mod(2ll * h - p.y + p.x, 2 * h)];
                dpUp[p.id] = max(dpUp[p.id], dpDown[m2[x].begin() -> id]);
            }
            
        } else {
            auto it = lower_bound(myLine -> begin(), myLine -> end(), p);
            it++;
            dpUp[p.id] = max(dpUp[p.id], dpUp[it -> id]);
        }
        
        myLine = &m2[p.y + p.x];
        if(p == myLine -> back()) {
            
            if(l2.find(mod(p.y + p.x, 2 * h)) != l2.end()) {
                long long x = l2[mod(p.y + p.x, 2 * h)];
                dpDown[p.id] = max(dpDown[p.id], dpDown[m2[x].begin() -> id]);
            }
            
            if(l1.find(mod(- p.y - p.x, 2 * h)) != l1.end()) {
                long long x = l1[mod(- p.y - p.x, 2 * h)];
                dpDown[p.id] = max(dpDown[p.id], dpUp[m1[x].begin() -> id]);
            }
            
        } else {
            auto it = lower_bound(myLine -> begin(), myLine -> end(), p);
            it++;
            dpDown[p.id] = max(dpDown[p.id], dpDown[it -> id]);
        }
        
        if(p.type == COIN) {
            dpUp[p.id]++;
            dpDown[p.id]++;
        }
        
        if(p.type == BOARD) {
            dpUp[p.id] = max(dpUp[p.id], dpDown[p.id]);
            dpDown[p.id] = max(dpUp[p.id], dpDown[p.id]);
        }
        
        l1[mod(p.y - p.x, 2 * h)] = p.y - p.x;
        l2[mod(p.y + p.x, 2 * h)] = p.y + p.x;
    }
    
    int result = 0;
    
    if(l1.find(0) != l1.end()) {
        result = max(result, dpUp[m1[l1[0]].begin() -> id]);
    }
    
    if(l2.find(0) != l2.end()) {
        result = max(result, dpDown[m2[l2[0]].begin() -> id]);
    }
    
    printf("%d\n", result);
}
    
int32_t main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
