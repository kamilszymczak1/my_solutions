#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct point {
    long long x, y;
    point() {}
    point(long long _x, long long _y) : x(_x), y(_y) {}
};

long long operator^(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

bool angle_cmp(point a, point b) {
    return (a ^ b) > 0;
}

point operator+ (point a, point b) {
    return point(a.x + b.x, a.y + b.y);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<point>upper, lower;
    
    point bottom_left(0, 0);
    
    for(int i = 0; i < n; i++) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        long long x = a - b;
        long long y = c - d;
        
        if(x == 0 && y == 0)
            continue;
        
        if(y < 0 || (y == 0 && x < 0))
            bottom_left = bottom_left + point(x, y);
        
        if(y > 0 || (y == 0 && x > 0)) {
            upper.emplace_back(x, y);
            lower.emplace_back(-x, -y);
        } else {
            upper.emplace_back(-x, -y);
            lower.emplace_back(x, y);
        }
    }
    
    sort(upper.begin(), upper.end(), angle_cmp);
    sort(lower.begin(), lower.end(), angle_cmp);
    
    vector<point>hull = {bottom_left};
    for(point p : upper)
        hull.emplace_back(hull.back() + p);
    for(point p : lower)
        hull.emplace_back(hull.back() + p);
    
    long double result = 0;
    for(auto [x, y] : hull) {
        long double dx = x;
        long double dy = y;
        result = max(result, dx * dx + dy * dy);
    }
    
    cout << fixed << setprecision(12) << result << '\n';
    
    return 0;
}
