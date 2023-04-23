#include <iostream>
#include <vector>

#define MAX_N 7000

using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int a, int b);
};

struct Rectangle {
    Point a, b;
    Rectangle() {}
    Rectangle(Point aa, Point bb);
};

Rectangle rects[MAX_N];
int set[MAX_N];
int n;

void MakeSet(int i);
int Find(int i);
bool Union(int a, int b);

void ReadData();
inline bool Intersects(Rectangle &a, Rectangle &b);
inline bool operator== (const Point &a, const Point &b);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int result = n;
    
    for(int i = 0; i < n; i++)
        MakeSet(i);
    
    for(int i = 0; i < n; i++)
        for(int j = i - 1; j >= 0; j--)
            if(Intersects(rects[i], rects[j]) && Union(i, j))
                result--;
    
    cout << result << "\n";
            
    return 0;
    
}

void MakeSet(int i) {
    set[i] = -1;
}

int Find(int i) {
    if(set[i] < 0)
        return i;
    set[i] = Find(set[i]);
    return set[i];
}

bool Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if(a == b)
        return false;
    if(set[a] < set[b])
        set[b] = a;
    else {
        if(set[a] == set[b])
            set[b]--;
        set[a] = b;
    }
    return true;
}

inline bool Intersects(Rectangle &a, Rectangle &b) {
    if(a.a == b.b || b.a == a.b || Point(a.b.x, a.a.y) == Point(b.a.x, b.b.y) ||
        Point(b.b.x, b.a.y) == Point(a.a.x, a.b.y))
        return false;
    
    int x[4], y[4];
    x[0] = a.a.x; x[1] = a.b.x; y[0] = a.a.y; y[1] = a.b.y;
    x[2] = b.a.x; x[3] = b.b.x; y[2] = b.a.y; y[3] = b.b.y;
    
    if(abs(x[0] - x[1]) > abs(x[2] - x[3]))
        swap(x[0], x[2]), swap(x[1], x[3]);
    if(abs(y[0] - y[1]) > abs(y[2] - y[3]))
        swap(y[0], y[2]), swap(y[1], y[3]);
    
    return (((x[0] >= x[2] && x[0] <= x[3]) || (x[1] >= x[2] && x[1] <= x[3])) 
    && ((y[0] >= y[2] && y[0] <= y[3]) || (y[1] >= y[2] && y[1] <= y[3])));
}

void ReadData() {
    int x[2], y[2];
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++)
            cin >> x[j] >> y[j];
        rects[i] = Rectangle(Point(x[0], y[0]), Point(x[1], y[1]));
    }
}


Point::Point(int a, int b) {
    x = a;
    y = b;
}

Rectangle::Rectangle(Point aa, Point bb) {
    a = aa;
    b = bb;
}

inline bool operator== (const Point &a, const Point &b) {
    return a.x == b.x && a.y == b.y;
}
