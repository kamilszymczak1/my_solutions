#include <iostream>
#include <stack>
#include <queue>
#include <set>
const int MAX_N = 107, inf = 99999999;
const int moves[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
int n, m, base, bcsCount = 0;
bool isFree[4 * MAX_N * MAX_N], visited[MAX_N * MAX_N];
int pre[MAX_N * MAX_N], low[MAX_N * MAX_N], dist[4 * MAX_N * MAX_N];
std::set<int>bcs[MAX_N * MAX_N];
struct Point {
    int x, y, z;
    Point(int _x, int _y) : x(_x), y(_y), z(0) {}
    Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    Point() {};
    int get() {return z * base * base + x * base + y;}
};
struct Edge {
    Point a, b;
    Edge(Point _a, Point _b) : a(_a), b(_b) {}
};
bool operator== (Point a, Point b) {return a.x == b.x && a.y == b.y;}
bool operator!= (Point a, Point b) {return a.x != b.x || a.y != b.y;}
Point guy, pack, target, start(0, 0, 0);

void ReadData() {
    std::string s;
    std::cin >> n >> m;
    base = std::max(n, m) + 2;
    for(int i = 0; i < n; i++) {
        std::cin >> s;
        for(int j = 0; j < m; j++) { 
            for(int k = 0; k < 4; k++)
                isFree[Point(i + 1, j + 1, k).get()] = (s[j] != 'S');
            if(s[j] == 'P')
                pack = Point(i + 1, j + 1);
            if(s[j] == 'K')
                target = Point(i + 1, j + 1);
            if(s[j] == 'M')
                guy = Point(i + 1, j + 1);
        }
    }
}

void DFS(Point v, Point p, std::stack<Edge>&s, int &time) {
    visited[v.get()] = true;
    pre[v.get()] = low[v.get()] = ++time;
    int child = 0;
    for(int i = 0; i < 4; i++) {
        Point u(v.x + moves[i][0], v.y + moves[i][1]);
        if(!isFree[u.get()])
            continue;
        if(u == pack && start.x == 0)
            start = Point(u.x, u.y, (i + 2) & 3);
        
        if(!visited[u.get()]) {
            child++;
            s.push(Edge(v, u));
            DFS(u, v, s, time);
            low[v.get()] = std::min(low[v.get()], low[u.get()]);
            if((pre[v.get()] == 1 && child > 1) || (pre[v.get()] > 1 && low[u.get()] >= pre[v.get()])) {
                bcsCount++;
                while(!(s.top().a == v && s.top().b == u)) {
                    bcs[s.top().a.get()].insert(bcsCount);
                    bcs[s.top().b.get()].insert(bcsCount);
                    s.pop();
                }
                bcs[s.top().a.get()].insert(bcsCount);
                bcs[s.top().b.get()].insert(bcsCount);
                s.pop();
            } 
        } else if(u != p && pre[u.get()] < low[v.get()]) {
            low[v.get()] = pre[u.get()];
            s.push(Edge(v, u));
        } 
    }
}

void FindBiconnected() {
    std::stack<Edge>s;
    int time = 0;
    DFS(guy, Point(-1, -1), s, time);
    bcsCount++;
    while(!s.empty()) {
        bcs[s.top().a.get()].insert(bcsCount);
        bcs[s.top().b.get()].insert(bcsCount);
        s.pop();
    }
}

bool G(Point a, Point b) {
    for(auto it = bcs[a.get()].begin(); it != bcs[a.get()].end(); it++)
        if(bcs[b.get()].find(*it) != bcs[b.get()].end())
            return true;
    return false;
}

void BFS() {
    std::queue<Point>q;
    std::fill(dist, dist + 4 * MAX_N * MAX_N, inf);
    q.push(start);
    dist[start.get()] = 0;
    while(!q.empty()) {
        Point v = q.front();
        q.pop();
        Point mp(v.x + moves[v.z][0], v.y + moves[v.z][1]);
        Point front(v.x + moves[(v.z + 2) & 3][0], v.y + moves[(v.z + 2) & 3][1], v.z);
        
        if(isFree[front.get()] && dist[front.get()] > dist[v.get()] + 1) {
            dist[front.get()] = dist[v.get()] + 1;
            q.push(front);
        }
        
        for(int i = 0; i < 4; i++) {
            Point newmp(v.x + moves[i][0], v.y + moves[i][1]);
            Point u(v.x, v.y, i);
            if(isFree[newmp.get()] && G(mp, newmp) && dist[u.get()] > dist[v.get()]) {
                dist[u.get()] = dist[v.get()];
                q.push(u);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(0); 
    ReadData();
    FindBiconnected();
    BFS();
    int result = inf;
    for(int i = 0; i < 4; i++)
        result = std::min(result, dist[Point(target.x, target.y, i).get()]);
    if(result == inf)
        std::cout << "NIE\n";
    else
        std::cout << result << '\n';
    return 0;
}
