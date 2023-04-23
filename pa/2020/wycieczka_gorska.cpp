#include <iostream>
#include <queue>
using namespace std;
struct Point {
    int a, b;
    Point(int _a, int _b) : a(_a), b(_b) {}
};
const int MAX_N = 2007, MAX_K = 1000007;
const long long inf = 999999999999999999;
long long dist[MAX_N][MAX_N], n, m, k, t, bestTime = inf, bestCount = 0;
bool visited[MAX_N][MAX_N];
void ReadData(), BFS();
int main() {
    ios_base::sync_with_stdio(0);
    ReadData();
    BFS();
    long long a, b, d = dist[n - 1][m - 1] - n - m + 2;
    for(int i = 0; i < k; i++) {
        cin >> a >> b;
        t = (n + m - 2) * a + d * (b + a) / 2;
        if(t < bestTime)
            bestTime = t, bestCount = 1;
        else if(t == bestTime)
            bestCount++;
    }
    cout << bestTime << ' ' << bestCount << '\n';
    return 0;
}

void go(int a, int b, queue<Point>&q, int d) {
    if(a < 0 || b < 0 || a >= n || b >= m || visited[a][b])
        return;
    visited[a][b] = true;
    dist[a][b] = d;
    q.push(Point(a, b));
}

void BFS() {
    const int mov[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    queue<Point>q;
    q.push(Point(0, 0));
    visited[0][0] = true;
    dist[0][0] = 0;
    while(!q.empty()) {
        Point p = q.front();
        q.pop();
        for(int i = 0; i < 4; i++)
            go(p.a + mov[i][0], p.b + mov[i][1], q, dist[p.a][p.b] + 1);
    }
}

void ReadData() {
    cin >> n >> m >> k;
    string s;
    for(int i = 0, j; i < n; i++)
        for(j = 0, cin >> s; j < m; j++)
            visited[i][j] = (s[j] == 'X') ? true : false, dist[i][j] = inf;
}
