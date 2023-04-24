#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

const int moves[8][2] = { {0, -1}, {0, 1}, {1, 0}, {-1, 0},
{1, -1}, {1, 1}, {-1, 1}, {-1, -1} };

bool Valid(int x, int y, vector<vector<int>>&grid) {
    vector<int>v = {grid[x][y], grid[x + 1][y], grid[x][y + 1], grid[x + 1][y + 1]};
    sort(v.begin(), v.end());
    int i = 0;
    while(i < 4 && v[i] == -1)
        i++;
    return i == 4 || v[i] == v[3];
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<vector<int>>grid(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];
        
        vector<vector<bool>>visited(n - 1, vector<bool>(m - 1, false));
    
    queue<pair<int, int>>q;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < m - 1; j++) {
            if(Valid(i, j, grid)) {
                q.push(make_pair(i, j));
                visited[i][j] = true;
            }
        }
    }
    
    stack<pair<pair<int, int>, int>>s;
    
    while(!q.empty()) {
        pair<int, int>p = q.front();
        int a = p.first, b = p.second;
        int colour = max({grid[a][b], grid[a + 1][b], grid[a][b + 1], grid[a + 1][b + 1], 1});
        grid[a][b] = grid[a + 1][b] = grid[a][b + 1] = grid[a + 1][b + 1] = -1;
        s.push(make_pair(make_pair(a, b), colour));
        for(int i = 0; i < 8; i++) {
            int A = p.first + moves[i][0], B = p.second + moves[i][1];
            if(0 <= A && A < n - 1 && 0 <= B && B < m - 1 && !visited[A][B]) {
                if(Valid(A, B, grid)) {
                    q.push(make_pair(A, B));
                    visited[A][B] = true;
                }
            }
        }
        
        q.pop();
    }
    
    int sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            sum += grid[i][j];
        
        if(-sum != n * m) {
            cout << "-1\n";
            return 0;
        }
        
        cout << s.size() << '\n';
    while(!s.empty()) {
        cout << s.top().first.first + 1 << ' ' << s.top().first.second + 1 << ' ' << s.top().second << '\n';
        s.pop();
    }
    
    return 0;
}
