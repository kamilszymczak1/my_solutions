#include <iostream>
#include <queue>

using namespace std;
constexpr long long inf = 1ll << 59;
constexpr int MAX_N = 2007;

long long dist[2][MAX_N][MAX_N], w, grid[MAX_N][MAX_N];
int n, m;

vector<pair<int, int>>moves = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

bool validTile(int i, int j) {
    return i >= 0 && j >= 0 && i < n && j < m && grid[i][j] >= 0;
}

void BFS(int k, pair<int, int>beg) {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            dist[k][i][j] = inf;
        dist[k][beg.first][beg.second] = 0;
    queue<pair<int, int>>q;
    for(q.push(beg); !q.empty(); q.pop()) {
        auto [x, y] = q.front();
        for(auto [a, b] : moves) {
            if(validTile(x + a, y + b) && dist[k][x + a][y + b] > dist[k][x][y] + w) {
                dist[k][x + a][y + b] = dist[k][x][y] + w;
                q.emplace(x + a, y + b);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> w;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    BFS(0, make_pair(0, 0));
    BFS(1, make_pair(n - 1, m - 1));
    long long result = dist[0][n - 1][m - 1], best[2] = {inf, inf};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] > 0) {
                for(int k = 0; k < 2; k++) {
                    best[k] = min(best[k], dist[k][i][j] + grid[i][j]);
                }
            }
            
        }
    } 
    result = min(result, best[0] + best[1]);
    if(result < inf) {
        cout << result << '\n';
    } else {
        cout << "-1\n";
    }
    return 0;
}
