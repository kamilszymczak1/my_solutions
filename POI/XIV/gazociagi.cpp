#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

const int SOURCE = 0, TARGET = 1;
const int MAX_N = 50000;

struct Point {
    int x, y, index, type, newIndex;
    Point() {}
    Point(int _x, int _y, int _index, int _type) : x(_x), y(_y), index(_index), type(_type) {}
    bool operator() (Point a, Point b) {
        if(a.x == b.x)
            return a.type < b.type;
        return a.x < b.x;
    }
};

bool operator< (Point a, Point b) {
    return a.y < b.y;
}

Point points[MAX_N * 2];
int match[MAX_N];
int n;

void ReadData();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    multiset<Point>s;
    
    long long totalCost = 0;
    
    for(int i = 0; i < n + n; i++) {
        if(points[i].type == SOURCE)
            s.insert(points[i]);
        else {
            auto it = s.lower_bound(Point(0, points[i].y, 0, 0));
            if(it -> y < points[i].y)
                it++;
            totalCost += abs(it -> x - points[i].x) + abs(it -> y - points[i].y);
            match[it -> index] = points[i].index;
            s.erase(it);
        }
    }
    
    cout << totalCost << "\n";
    
    for(int i = 0; i < n; i++)
        cout << i + 1 << " " << match[i] + 1 - n << "\n";
    
    return 0;
}

void ReadData() {
    int x, y;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        points[i] = Point(x, y, i, SOURCE);
    }
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        points[i + n] = Point(x, y, i + n, TARGET);
    }
    sort(points, points + 2 * n, Point());
}
