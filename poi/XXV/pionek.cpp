#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct point {
    long long x, y;
    point() {}
    point(long long _x, long long _y) : x(_x), y(_y) {}
    long long dist_from_origin() {
        return x * x + y * y;
    }
};

long long operator^ (point a, point b) {
    return a.x * b.y - a.y * b.x;
}

bool angle_cmp(point a, point b) {
    return (a ^ b) > 0;
}

point operator+(point a, point b) {
    return point(a.x + b.x, a.y + b.y);
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<point>upper, lower;
    point bottom_left(0, 0);
    
    for(int i = 0; i < n; i++) {
        long long x, y; cin >> x >> y;
        
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
    
    point current = bottom_left;
    long long result = current.dist_from_origin();
    for(point p : upper) {
        current = current + p;
        result = max(result, current.dist_from_origin());
    }
    for(point p : lower) {
        current = current + p;
        result = max(result, current.dist_from_origin());
    }
    
    cout << result << '\n';
    
    return 0;
}
