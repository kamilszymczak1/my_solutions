#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>

#define MAX_N 100
#define inf 99999999

#define north 0
#define east 1
#define south 2
#define west 3
#define none 55555

using namespace std;

struct Point {
    int x, y, from;
    Point() {}
    Point(int a, int b, int d) {
        x = a;
        y = b;
        from = d;
    }
};

Point start, finish;

const int moves[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int visited[4][MAX_N][MAX_N];
int dist[4][MAX_N][MAX_N];
Point from[4][MAX_N][MAX_N];
int h, w;

void ReadData();
void Extend(Point p, queue<Point>&q, int d, int f);

void BFS();

int main() {
    ios_base::sync_with_stdio(0);
    ReadData();
    
    BFS();
    
    return 0;
}

void BFS() {
    if(dist[0][start.y][start.x] == -1 || dist[0][finish.y][finish.x] == -1) {
        cout << "NIE\n";
        return;
    }
    
    queue<Point>q;
    
    for(int k = 0; k < 4; k++)
        for(int i = 0; i < h; i++)
            for(int j = 0; j < w; j++)
                dist[k][i][j] = dist[k][i][j] == -1 ? -1 : inf;
    
    for(int i = 0; i < 4; i++) {
        dist[i][start.y][start.x] = 1;
        visited[i][start.y][start.x] = true;
        Extend(Point(start.x + moves[i][0], start.y + moves[i][1], (i + 2) % 4), q, 2, 0);
    }
        
    
    while(!q.empty()) {
        Point p = q.front();
        q.pop();
        
        for(int i = 0; i < 4; i++) {
            if(i == p.from || i == (p.from + 3) % 4)
                continue;
            int newDist = dist[p.from][p.y][p.x] + 1;
            int newX = p.x + moves[i][0];
            int newY = p.y + moves[i][1];
            Extend(Point(newX, newY, (i + 2) % 4), q, newDist, p.from);
        }
    }
    
    int best = inf, index;
    for(int i = 0; i < 4; i++) {
        if(dist[i][finish.y][finish.x] < best) {
            best = dist[i][finish.y][finish.x];
            index = i;
        }
    }
        
    if(best == inf) {
        cout << "NIE\n";
        return;
    }
    
    stack<Point>result;
    
    Point pos(finish.x, finish.y, index);
    
    while(pos.x != start.x || pos.y != start.y) {
        result.push(pos);
        Point newPos = from[pos.from][pos.y][pos.x];
        pos = newPos;
    }
    result.push(pos);
    
    cout << result.size() << "\n";
    while(!result.empty()) {
        Point p = result.top();
        result.pop();
        cout << p.y + 1 << " " << p.x + 1 << "\n";
    }
}

void Extend(Point p, queue<Point>&q, int d, int f) {
    if(p.x >= 0 && p.y >= 0 && p.x < w && p.y < h && !visited[p.from][p.y][p.x] && dist[0][p.y][p.x] != -1) {
        q.push(p);
        visited[p.from][p.y][p.x] = true;
        dist[p.from][p.y][p.x] = d;
        
        int fromX = p.x + moves[p.from][0];
        int fromY = p.y + moves[p.from][1];
        from[p.from][p.y][p.x] = {fromX, fromY, f};
    }
}

void ReadData() {
    string s;
    cin >> h >> w;
    for(int i = 0; i < h; i++) {
        cin >> s;
        for(int j = 0; j < w; j++)
            if(s[j] == '1')
                for(int k = 0; k < 4; k++)
                    dist[k][i][j] = -1;
            
    }
    cin >> start.y >> start.x >> finish.y >> finish.x;
    start.x--; start.y--; finish.x--; finish.y--;
}
