#include <cstdio>
#include <vector>
#include <algorithm>

#define LSB(x) (x & (-x))

using namespace std;

struct FenwickTree {
    vector<int>values;
    FenwickTree(int n) {
        values.resize(n + 1);
    }
    void Insert(int x, int value) {
        for(x++; x < values.size(); x += LSB(x))
            values[x] = max(values[x], value);
    }
    int MaxPrefix(int x) {
        int result = 0;
        for(x++; x; x -= LSB(x))
            result = max(result, values[x]);
        return result;
    }
};

struct Point {
    int x, y, p;
    Point() {}
    Point(int _x, int _y, int _p) : x(_x), y(_y), p(_p) {}
};

bool cmp1(Point &a, Point &b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmp2(Point &a, Point &b) {
    if(a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

int main() {
    int n, m, k; scanf("%d%d%d", &n, &m, &k);
    vector<Point>P(k);
    for(Point &p : P)
        scanf("%d%d%d", &p.x, &p.y, &p.p);
    sort(P.begin(), P.end(), cmp2);
    for(int i = 0; i < k; i++)
        P[i].y = i;
    sort(P.begin(), P.end(), cmp1);
    FenwickTree T(k);
    for(Point p : P)
        T.Insert(p.y, p.p + T.MaxPrefix(p.y));
    printf("%d\n", T.MaxPrefix(k - 1));
}
