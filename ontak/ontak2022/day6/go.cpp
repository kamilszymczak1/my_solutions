#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const long long M = 100'000;

double Dijkstra(vector<vector<pair<int, double>>>&adj, int s, int t) {
    int n = adj.size();
    vector<double>d(n, 1e100);
    d[s] = 0;
    set<pair<double, int>>bag;
    bag.insert(make_pair(d[s], s));
    while(!bag.empty()) {
        auto [k, x] = *bag.begin();
        bag.erase(bag.begin());
        if(k != d[x])
            continue;
        for(auto [y, w] : adj[x]) {
            if(d[y] > d[x] + w) {
                d[y] = d[x] + w;
                bag.insert(make_pair(d[y], y));
            }
        }
    }
    return d[t];
}

struct Point {
    long long x, y;
    Point() {}
    Point(long long _x, long long _y) : x(_x), y(_y) {}
};

Point operator- (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }
Point operator+ (Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
bool operator< (Point a, Point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }
long long operator^ (Point a, Point b) { return a.x * b.y - a.y * b.x; }
Point operator *(long long x, Point a) { return Point(a.x * x, a.y * x); }

struct Segment {
    Point a, b;
    Segment() {}
    Segment(Point _a, Point _b) : a(_a), b(_b) {}
    Segment(long long _x1, long long _y1, long long _x2, long long _y2) {
        a = Point(_x1, _y1);
        b = Point(_x2, _y2);
    }
    Point Middle() { return Point((a.x + b.x) / 2, (a.y + b.y) / 2); }
};

double D(Point a, Point b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

long long sgn(long long x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }

bool SegmentIntersection(Segment s1, Segment s2) {
    if(max(s1.a.x, s1.b.x) < min(s2.a.x, s2.b.x) || max(s2.a.x, s2.b.x) < min(s1.a.x, s1.b.x))
        return false;
    Point a, b, c;
    a = s1.a - s2.a, b = s1.b - s2.a, c = s2.b - s2.a;
    long long w1 = sgn(a ^ c) * sgn(b ^ c);
    a = s2.a - s1.a, b = s2.b - s1.a, c = s1.b - s1.a;
    long long w2 = sgn(a ^ c) * sgn(b ^ c);
    return w1 <= 0 && w2 <= 0;
}

bool PointInPolygon(vector<Point>&p, Point P) {
    Segment s(P, Point(P.x + 1, M));
    int n = p.size(), intersections = 0;
    for(int i = 0; i < n; i++)
        intersections += SegmentIntersection(Segment(p[i], p[(i + 1) % n]), s);
    return intersections % 2 == 1;
}

int main() {
    int n; scanf("%d", &n);
    
    vector<Point>inner(n);
    for(auto &[x, y] : inner) {
        scanf("%lld%lld", &x, &y);
        x *= 2; y *= 2;
    }
        
    int m; scanf("%d", &m);
    vector<Point>outer(m);
    for(auto &[x, y] : outer) {
        scanf("%lld%lld", &x, &y);
        x *= 2; y *= 2;
    }
    
    vector<Segment>hulls;
    vector<vector<pair<int, double>>>adj(n + m + 1);
    
    int leftmost = min_element(inner.begin(), inner.end()) - inner.begin();
    
    Point finishMiddle = Segment(inner[(leftmost + 1) % n], inner[(leftmost - 1 + n) % n]).Middle();
    Point offset = inner[leftmost] - finishMiddle;
    Segment finishLine = Segment(inner[leftmost] + M * offset, inner[leftmost]);
    finishLine.a.y++;
    
    for(int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if(!SegmentIntersection(Segment(inner[i], inner[j]), finishLine)) {
            adj[i].emplace_back(j, D(inner[i], inner[j]));
            adj[j].emplace_back(i, D(inner[i], inner[j]));
        }
        hulls.emplace_back(inner[i], inner[j]);
    }
    
    for(int i = 0; i < m; i++) {
        int j = (i + 1) % m;
        if(!SegmentIntersection(Segment(outer[i], outer[j]), finishLine)) {
            adj[i + n].emplace_back(j + n, D(outer[i], outer[j]));
            adj[j + n].emplace_back(i + n, D(outer[i], outer[j]));
        }
        hulls.emplace_back(outer[i], outer[j]);
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            Segment s = Segment(inner[i], outer[j]);
            
            
            int intersections = SegmentIntersection(finishLine, s);
            for(Segment t : hulls)
                intersections += SegmentIntersection(t, s);
            
            if(intersections == 4) {
                adj[i].emplace_back(j + n, D(inner[i], outer[j]));
                adj[j + n].emplace_back(i, D(inner[i], outer[j]));
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 2; j < n; j++) {
            if(i == 0 && j == n - 1)
                continue;
            Segment s = Segment(inner[i], inner[j]);
            int intersections = SegmentIntersection(finishLine, s);
            for(Segment t : hulls)
                intersections += SegmentIntersection(t, s);
            
            if(intersections == 4 && !PointInPolygon(inner, s.Middle())) {
                adj[i].emplace_back(j, D(inner[i], inner[j]));
                adj[j].emplace_back(i, D(inner[i], inner[j]));
            }
        }
    }
    
    for(int i = 0; i < m; i++) {
        for(int j = i + 2; j < m; j++) {
            if(i == 0 && j == m - 1)
                continue;
            Segment s = Segment(outer[i], outer[j]);
            int intersections = SegmentIntersection(finishLine, s);
            for(Segment t : hulls)
                intersections += SegmentIntersection(s, t);
            
            if(intersections == 4 && PointInPolygon(outer, s.Middle())) {
                adj[i + n].emplace_back(j + n, D(outer[i], outer[j]));
                adj[j + n].emplace_back(i + n, D(outer[i], outer[j]));
            }
        }
    }
    
    adj[leftmost].emplace_back((leftmost + 1) % n, D(inner[leftmost], inner[(leftmost + 1) % n]));
    adj[(leftmost + 1) % n].emplace_back(leftmost, D(inner[leftmost], inner[(leftmost + 1) % n]));
    
    adj[n + m].emplace_back((leftmost - 1 + n) % n, D(inner[leftmost], inner[(leftmost - 1 + n) % n]));
    adj[(leftmost - 1 + n) % n].emplace_back(n + m, D(inner[leftmost], inner[(leftmost - 1 + n) % n]));
    
    for(int i = 0; i < n; i++) {
        if(i == (leftmost - 1 + n) % n || i == leftmost || i == (leftmost + 1) % n)
            continue;
        
        int intersections = 0;
        Segment s(inner[i], inner[leftmost]);
        for(Segment t : hulls)
            intersections += SegmentIntersection(s, t);
        
        if(intersections == 4 && !PointInPolygon(inner, s.Middle())) {
            
            long long w = (finishLine.a - finishLine.b) ^ (s.a - s.b);
            
            if(w < 0) {
                adj[n + m].emplace_back(i, D(inner[leftmost], inner[i]));
                adj[i].emplace_back(n + m, D(inner[leftmost], inner[i]));
            }
            
            if(w > 0) {
                adj[leftmost].emplace_back(i, D(inner[leftmost], inner[i]));
                adj[i].emplace_back(leftmost, D(inner[leftmost], inner[i]));
            }
            
        }
    }
    
    for(int i = 0; i < m; i++) {
        
        int intersections = 0;
        Segment s(outer[i], inner[leftmost]);
        for(Segment t : hulls)
            intersections += SegmentIntersection(s, t);
        
        if(intersections == 4) {
            long long w = (finishLine.a - finishLine.b) ^ (s.a - s.b);
            
            if(w < 0) {
                adj[n + m].emplace_back(i + n, D(inner[leftmost], outer[i]));
                adj[i + n].emplace_back(n + m, D(inner[leftmost], outer[i]));
            }
            
            if(w > 0) {
                adj[leftmost].emplace_back(i + n, D(inner[leftmost], outer[i]));
                adj[i + n].emplace_back(leftmost, D(inner[leftmost], outer[i]));
            }
        }
    }
    
    
    printf("%.15F\n", Dijkstra(adj, leftmost, n + m) / 2);
    
    return 0;
}
