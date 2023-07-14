#include <iostream>
#include <vector>
#include <queue>
    
using namespace std;
    
const int MAX_N = 1001;
    
int n, m;
bool visited[MAX_N][MAX_N], grid[MAX_N][MAX_N];
const int moves[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
pair<int, int>parent[MAX_N][MAX_N];
char answer[MAX_N][MAX_N];
const int inf = 1 << 30;
    
bool can_go_lake(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= m)
        return false;
    if(visited[x][y] || grid[x][y] == false)
        return false;
    return true;
}
    
bool can_go_road(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= m)
        return false;
    if(visited[x][y] || grid[x][y] == true)
        return false;
    return true;
}
    
void dfs_gather(int x, int y, vector<pair<int, int>>&nodes) {
    nodes.emplace_back(x, y);
    visited[x][y] = true;
    for(int i = 0; i < 4; i++) {
        int xx = x + moves[i][0];
        int yy = y + moves[i][1];
        if(can_go_lake(xx, yy)) {
            dfs_gather(xx, yy, nodes);
        }
    }
}
    
void bfs(int x, int y) {
    queue<pair<int, int>>q;
    q.push(make_pair(x, y));
    visited[x][y] = true;
    while(!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int xx = x + moves[i][0];
            int yy = y + moves[i][1];
            if(can_go_road(xx, yy)) {
                parent[xx][yy] = make_pair(x, y);
                visited[xx][yy] = true;
                q.push(make_pair(xx, yy));
            }
        }
    }
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            grid[i][j] = s[j] == '.';
        }
    }
    
    
    for(int i = 0; i < n; i++) {
        if(grid[i][0] == true && !visited[i][0]) {
            vector<pair<int, int>>cells;
            dfs_gather(i, 0, cells);
        }
        if(grid[i][m - 1] == true && !visited[i][m - 1]) {
            vector<pair<int, int>>cells;
            dfs_gather(i, m - 1, cells);
        }
    }
    
    for(int i = 0; i < m; i++) {
        if(grid[0][i] == true && !visited[0][i]) {
            vector<pair<int, int>>cells;
            dfs_gather(0, i, cells);
        }
        if(grid[n - 1][i] == true && !visited[n - 1][i]) {
            vector<pair<int, int>>cells;
            dfs_gather(n - 1, i, cells);
        }
    }
    
    vector<pair<int, int>>lake_cells;
    for(int i = 1; i < n - 1; i++) {
        for(int j = 1; j < m - 1; j++) {
            if(grid[i][j] == true && !visited[i][j]) {
                dfs_gather(i, j, lake_cells);
            }
        }
    }
    
    
    pair<int, int>topmost = make_pair(n, 0);
    pair<int, int>bottommost = make_pair(-1, 0);
    
    for(auto p : lake_cells) {
        topmost = min(topmost, p);
        bottommost = max(bottommost, p);
    }
    
    for(int i = bottommost.first + 1; i < n; i++)
        visited[i][bottommost.second] = true;
    for(int i = topmost.first - 1; i >= 0; i--)
        visited[i][topmost.second] = true;
    
    bfs(topmost.first - 1, topmost.second + 1);
    bfs(topmost.first - 1, topmost.second - 1);
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            answer[i][j] = '.';
        
    answer[bottommost.first + 1][bottommost.second] = '#';
    answer[topmost.first - 1][topmost.second] = '#';
    
    pair<int, int>current = make_pair(bottommost.first + 1, bottommost.second + 1);
    while(current != make_pair(topmost.first - 1, topmost.second + 1)) {
        answer[current.first][current.second] = '#';
        current = parent[current.first][current.second];
    }
    answer[current.first][current.second] = '#';
    
    current = make_pair(bottommost.first + 1, bottommost.second - 1);
    while(current != make_pair(topmost.first - 1, topmost.second - 1)) {
        answer[current.first][current.second] = '#';
        current = parent[current.first][current.second];
    }
    answer[current.first][current.second] = '#';
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << answer[i][j];
        }
        cout << '\n';
    }
    
    
    return 0;
}
