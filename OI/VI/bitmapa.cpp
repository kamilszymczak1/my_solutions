#include <iostream>
#include <queue>
#define SIZE 200
#define inf 10000000

using namespace std;

struct Point {
    int x, y;
    Point(int a, int b) {x = a; y = b;}
};

int d[SIZE][SIZE];
int n, m;
queue<Point>q;

inline void load();
inline void print();
inline void calculate_result();
inline void go(int x,int y,int distance);

int main() {
    ios_base::sync_with_stdio(0);
    load();
    calculate_result();
    print();
}

inline void calculate_result() {
    while(!q.empty()) {
        Point p = q.front();
        q.pop();
        int x = p.x;
        int y = p.y;
        int distance = d[x][y];
        go(x + 1, y, distance);
        go(x - 1, y, distance);
        go(x, y + 1, distance);
        go(x, y - 1, distance);
    }
}

inline void go(int x, int y, int distance) {
    if(x >= 0 && y >= 0 && x < n && y < m && d[x][y] == inf) {
        d[x][y] = distance + 1;
        q.push(Point(x, y));
    }
}

inline void print() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << d[i][j] << " ";
        cout << "\n";
    }
}

inline void load() {
    string str;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> str;
        for(int j = 0; j < m; j++) {
            if(str[j] == '1') {
                q.push(Point(i, j));
                d[i][j] = 0;
            }
            else d[i][j] = inf;
        }
    }
}
