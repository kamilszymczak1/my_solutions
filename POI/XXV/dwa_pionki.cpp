#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAX_N = 400007;

struct Vector {
    long long x, y;
    Vector() : x(0), y(0) {}
    Vector(long long _x, long long _y) : x(_x), y(_y) {}
    long long abs() {
        return x * x + y * y;
    }
    long double angle() {
        if(y >= 0)
            return acos((long double)x / sqrt(x * x + y * y));
        return 2 * M_PI - acos((long double)x / sqrt(x * x + y * y));
    }
};

Vector operator+ (Vector a, Vector b) {
    return Vector(a.x + b.x, a.y + b.y);
}
Vector operator- (Vector a, Vector b) {
    return Vector(a.x - b.x, a.y - b.y);
}

bool cmp(Vector a, Vector b) {
    return a.angle() < b.angle();
}

Vector v[MAX_N], sum;
long long m[MAX_N];
long long n;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y;
        sum = sum + v[i];
        if(v[i].x == v[i].y && v[i].x == 0) {
            n--; i--;
        }
    }
    for(int i = 0; i < n; i++) {
        v[i + n].x = -v[i].x;
        v[i + n].y = -v[i].y;
    }
    n += n;
    sort(v, v + n, cmp);
    long long result = 0;
  
    int end = 0;
    Vector t = Vector(0, 0);
    for(int beg = 0; beg < n; beg++) {
        while(end < n && v[end].angle() - v[beg].angle() < M_PI) {
            result = max(result, t.abs());
            t = t + v[end++];
        }
        result = max(result, t.abs());
        t = t - v[beg];
    }
    cout << result << '\n';
    return 0;
}
