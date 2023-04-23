#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
const long long inf = 1ll << 30;
    
int input_int() {
    string s; cin >> s;
    while(s.size() < 8)
        s += '0';
    int x = 0;
    for(int i = 0; i < 6; i++) {
        x = x * 10 + s[i + 2] - '0';
    }
    return x;
}
    
struct point {
    long long x, y, w;
    point(long long _x, long long _y, long long _w) : x(_x), y(_y), w(_w) {}
    point() : x(0), y(0) {}
};
    
bool operator== (point a, point b) {
    return a.x == b.x && a.y == b.y && a.w == b.w;
}
    
long long operator^ (point a, point b) {
    return a.x * b.y - a.y * b.x;
}
    
long long left(point a, point b) {
    return (a ^ b) < 0;
}
    
bool angle_cmp(point &a, point &b) {
    
    if(a.y * b.y < 0)
        return a.y > b.y;
        
    if(a.y * b.y > 0)
        return left(b, a) || a == b;
    
    if(a.y == 0 && b.y == 0)
        return a.x > b.x;
    
    if(a.y == 0) {
        if(a.x >= 0)
            return true;
        return b.y < 0;
    }
    
    if(b.x >= 0)
        return false;
    return a.y > 0;
}
    
long long get(point origin, vector<point>points) {
    
    points.erase(find(points.begin(), points.end(), origin));
    for(auto &[x, y, w] : points) {
        x -= origin.x;
        y -= origin.y;
    }
        
    points.emplace_back(0, +inf, 0);
    points.emplace_back(0, -inf, 0);
    points.emplace_back(+inf, 0, 0);
    points.emplace_back(-inf, 0, 0);
    
    sort(points.begin(), points.end(), angle_cmp);
    
    int n = points.size();
    
    int j = 0;
    long long w_sum = 0, answer = 0;
    for(int i = 0; i < n; i++) {
        while(i == j || left(points[j], points[i])) {
            w_sum += points[j].w;
            j = (j + 1) % n;
        }
        answer = max(answer, w_sum);
        w_sum -= points[i].w;
    }
    return answer;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<point>points;
    for(int i = 0; i < n; i++) {
        int x = input_int();
        int y = input_int();
        points.emplace_back(x, y, 1);
    }
    for(int i = 0; i < m; i++) {
        int x = input_int();
        int y = input_int();
        points.emplace_back(x, y, -inf);
    }
    
    long long answer = 0;
    
    for(int i = 0; i < m; i++) {
        answer = max(answer, get(points[i + n], points));
    }
    
    cout << answer << '\n';
    
    return 0;
}
