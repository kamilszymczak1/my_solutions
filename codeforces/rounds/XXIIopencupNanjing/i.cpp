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
    map<int, int>m1, m2; //m1 for y = x + b, m2 for y = -x + b
    
    vector<int>dpUp(points.size()), dpDown(points.size());
    reverse(points.begin(), points.end());
    
    for(Point &p : points) {
        
        if(m1.find(mod(p.y - p.x, 2 * h)) != m1.end()) {
            long long x = m1[mod(p.y - p.x, 2 * h)];
            dpUp[p.id] = max(dpUp[p.id], dpUp[x]);
        }
        
        if(m2.find(mod(p.x - p.y, 2 * h)) != m2.end()) {
            long long x = m2[mod(p.x - p.y, 2 * h)];
            dpUp[p.id] = max(dpUp[p.id], dpDown[x]);
        }
        
        if(m2.find(mod(p.y + p.x, 2 * h)) != m2.end()) {
            long long x = m2[mod(p.y + p.x, 2 * h)];
            dpDown[p.id] = max(dpDown[p.id], dpDown[x]);
        }
        
        if(m1.find(mod(- p.y - p.x, 2 * h)) != m1.end()) {
            long long x = m1[mod(- p.y - p.x, 2 * h)];
            dpDown[p.id] = max(dpDown[p.id], dpUp[x]);
        }
        
        if(p.type == COIN) {
            dpUp[p.id]++;
            dpDown[p.id]++;
        }
        
        if(p.type == BOARD) {
            dpUp[p.id] = max(dpUp[p.id], dpDown[p.id]);
            dpDown[p.id] = max(dpUp[p.id], dpDown[p.id]);
        }
        
        m1[mod(p.y - p.x, 2 * h)] = p.id;
        m2[mod(p.y + p.x, 2 * h)] = p.id;
    }
    
    int result = 0;
    
    if(m1.find(0) != m1.end()) {
        result = max(result, dpUp[m1[0]]);
    }
    
    if(m2.find(0) != m2.end()) {
        result = max(result, dpDown[m2[0]]);
    }
    
    printf("%d\n", result);
}

int32_t main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
