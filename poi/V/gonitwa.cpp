#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 3000

#define inf 99999999

using namespace std;

vector<int>graph[MAX_N];
int dist[2][MAX_N];
int pre[MAX_N];
int start[2], n, m, count = 0;
bool visited[MAX_N];
bool inCycle[MAX_N];

void ReadData();
void BFS(int beg, int l); // l - layer
int DFS(int x, int p);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    for(int i = 0; i < 2; i++)
        BFS(start[i], i);
    
    DFS(0, -1);
    
    int result = 0;
    
    for(int i = 0; i < n; i++) {
        if(dist[0][i] < dist[1][i] && inCycle[i])
            result = inf;
        if(dist[0][i] < dist[1][i])
            result = max(result, dist[1][i]);
    }
    
    if(result == inf)
        cout << "NIE\n";
    else
        cout << result << "\n";
    
    return 0;
}

int DFS(int x, int p) {
    visited[x] = true;
    pre[x] = count++;
    int result = pre[x] + 1;
    for(int y : graph[x]) {
        if(!visited[y]) {
            int newResult = DFS(y, x);
            result = min(result, newResult);
        } else if(y != p)
            result = min(pre[y], result), inCycle[y] = true;
    }
    if(result < pre[x])
        inCycle[x] = true;
    return result;
}

void BFS(int beg, int l) {
    fill(dist[l], dist[l] + n, -1);
    queue<int>q;
    dist[l][beg] = 0;
    q.push(beg);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        
        for(int y : graph[x]) {
            if(dist[l][y] == -1) {
                dist[l][y] = dist[l][x] + 1;
                q.push(y);
            }
        }
    }
}


void ReadData() {
    int a, b;
    cin >> n >> m;
    for(int i = 0; i < 2; i++) {
        cin >> start[i];
        start[i]--;
    }
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
}
