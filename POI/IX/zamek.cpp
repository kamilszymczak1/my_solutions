#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define MAX_S 1000
#define MAX_N 100

using namespace std;

struct Point {
    int x, y;
    Point () {}
    Point(int a, int b) {
        x = a; y = b;
    }
};

int n, m, w, k, s;
vector<int>graph[MAX_N];
int cost[MAX_N];
int dist[MAX_S][MAX_N];
bool visited[MAX_S][MAX_N];
Point parent[MAX_S][MAX_N];

void ReadData();
bool Solve();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    if(Solve()) {
        stack<int>result;
        Point p(0, k);
        
        while(p.x != s || p.y != w) {
            result.push(p.y + 1);
            p = parent[p.x][p.y];
        }
        result.push(p.y + 1);
        
        while(!result.empty()) {
            cout << result.top() << " ";
            result.pop();
        }
        cout << "\n"; 
    } else
        cout << "NIE\n";
    
    return 0;
}

bool Solve() {
    s -= cost[w];
    dist[s][w] = 0;
    visited[s][w] = true;
    queue<Point>q;
    q.push(Point(s, w));
    
    while(!q.empty()) {
        Point p = q.front();
        q.pop();
        
        if(p.x == 0 && p.y == k)
            return true;
        
        for(int x : graph[p.y]) {
            int newCost = p.x - cost[x];
            if(newCost >= 0 && !visited[newCost][x]) {
                visited[newCost][x] = true;
                parent[newCost][x] = {p.x, p.y};
                dist[newCost][x] = dist[p.x][p.y] + 1;
                q.push(Point(newCost, x));
            }
        }
    }
    
    return false;
}

void ReadData() {
    int a, b;
    cin >> n >> m >> w >> k >> s;
    w--; k--;
    for(int i = 0; i < n; i++)
        cin >> cost[i];
    
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
}
