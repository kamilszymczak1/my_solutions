#include <iostream>
#include <vector>
#include <queue>
#include <set>

#define MAX_N 200
#define MAX_K 13
#define inf 99999999

using namespace std;

struct Edge {
    int to, mask;
    int cost;
    Edge(int a, int b, int c);
};

struct Point {
    int x, y;
    Point(int a, int b);
};

vector<Edge>graph[MAX_N];
int smith[MAX_N];
int dist[1 << MAX_K][MAX_N];
int n, m, p;

struct comp {
    inline bool operator() (const Point &a, const Point &b) const {
        if(dist[a.x][a.y] == dist[b.x][b.y]) {
            if(a.x == b.x)
                return a.y < b.y;
            return a.x < b.x;
        }
        return dist[a.x][a.y] < dist[b.x][b.y];
    }
};

void ReadData();
int Dijkstra();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int result = Dijkstra();
    
    cout << result << "\n";
    
    return 0;
}

int Dijkstra() {
    
    for(int i = 0; i < 1 << p; i++)
        for(int j = 0; j < n; j++)
            dist[i][j] = inf;
    int begMask = smith[0]; 
    dist[begMask][0] = 0;
    
    queue<Point>q;
    q.push(Point(begMask, 0));
        
    while(!q.empty()) {
        Point p = q.front();
        q.pop();
        
        int mask = p.x;
        
        for(Edge e : graph[p.y]) {
            int newMask = mask | smith[e.to];
            if((mask & e.mask) == e.mask && dist[newMask][e.to] > dist[p.x][p.y] + e.cost) {
                dist[newMask][e.to] = dist[p.x][p.y] + e.cost;
                q.push(Point(newMask, e.to));
            }
        }
    }
    int result = inf;
    
    for(int i = 0; i < (1 << p); i++)
        result = min(result, dist[i][n - 1]);
    
    return result == inf ? -1 : result;
}

void ReadData() {
    int k, a, b, time, rep, val, mask;
    cin >> n >> m >> p >> k;
    for(int i = 0; i < k; i++) {
        cin >> a >> rep;
        mask = 0;
        for(int j = 0; j < rep; j++) {
            cin >> val;
            mask |= 1 << (val - 1);
        }
        smith[a - 1] |= mask;
    }
    
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> time >> rep;
        mask = 0;
        for(int j = 0; j < rep; j++) {
            cin >> val;
            mask |= 1 << (val - 1);
        }
        graph[a - 1].push_back(Edge(b - 1, time, mask));
        graph[b - 1].push_back(Edge(a - 1, time, mask));
    }
}

Edge::Edge(int a, int b, int c) {
    to = a;
    cost = b;
    mask = c;
}

Point::Point(int a, int b) {
    x = a;
    y = b;
}
