#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 1007, inf = 1 << 28;
const int moves[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
char grid[MAX_N][MAX_N];
int n;
int s[MAX_N][MAX_N], e[MAX_N][MAX_N], bestV[MAX_N][MAX_N], bestH[MAX_N][MAX_N], d[MAX_N][MAX_N];
int bestSV[MAX_N][MAX_N], bestEV[MAX_N][MAX_N], bestSH[MAX_N][MAX_N], bestEH[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
pair<int, int>start, finish, parent[MAX_N][MAX_N];

bool ValidTile(int x, int y) {
    return grid[x][y] == '.';
}

void BFS(pair<int, int>source) {
    for(int i = 0; i < n + 2; i++) {
        for(int j = 0; j < n + 2; j++) {
            d[i][j] = inf;
        }
    }
    d[source.first][source.second] = 0;
    queue<pair<int, int>>q;
    for(q.push(source); !q.empty(); q.pop()) {
        int a = q.front().first, b = q.front().second;
        for(int i = 0; i < 4; i++) {
            int A = a + moves[i][0], B = b + moves[i][1];
            if(ValidTile(A, B) && d[A][B] > d[a][b] + 1) {
                parent[A][B] = q.front();
                d[A][B] = d[a][b] + 1;
                q.push(make_pair(A, B));
            }
        }
    }
}

int Check(pair<int, int>p) {
    if(grid[p.first][p.second] == 'X')
        return inf;
    int result = min(bestH[p.first][p.second], bestV[p.first][p.second]);
    result = min(result, bestSV[p.first][p.second] + bestEH[p.first][p.second]);
    result = min(result, bestEV[p.first][p.second] + bestSH[p.first][p.second]);
    return result;
}

void Detonate(pair<int, int>x) {
    for(int i = x.first; grid[i][x.second] != 'X'; i--)
        grid[i][x.second] = '.';
    for(int i = x.first; grid[i][x.second] != 'X'; i++)
        grid[i][x.second] = '.';
    for(int i = x.second; grid[x.first][i] != 'X'; i--)
        grid[x.first][i] = '.';
    for(int i = x.second; grid[x.first][i] != 'X'; i++)
        grid[x.first][i] = '.';
}

void CalcHorizontal(pair<int, int>x) {
    int row = x.first, l = x.second, r = x.second;
    while(grid[row][l - 1] != 'X')
        l--;
    while(grid[row][r + 1] != 'X')
        r++;
    int result = inf, bestE = inf, bestS = inf;
    for(int i = l; i <= r; i++) {
        bestS = min(bestS, s[row][i] - i);
        bestE = min(bestE, e[row][i] - i);
        result = min(result, bestS + e[row][i] + i);
        result = min(result, bestE + s[row][i] + i);
        bestSH[row][i] = min(bestSH[row][i], bestS + i);
        bestEH[row][i] = min(bestEH[row][i], bestE + i);
    }
    bestS = inf, bestE = inf;
    for(int i = r; i >= l; i--) {
        bestS = min(bestS, s[row][i] + i);
        bestE = min(bestE, e[row][i] + i);
        result = min(result, bestS + e[row][i] - i);
        result = min(result, bestE + s[row][i] - i);
        bestSH[row][i] = min(bestSH[row][i], bestS - i);
        bestEH[row][i] = min(bestEH[row][i], bestE - i);
    }
    for(int i = l; i <= r; i++) {
        bestH[row][i] = result;
        visited[row][i] = true;
    }
        
}

void CalcVertical(pair<int, int>x) {
    int column = x.second, u = x.first, d = x.first;
    while(grid[u + 1][column] != 'X')
        u++;
    while(grid[d - 1][column] != 'X')
        d--;
    int result = inf, bestE = inf, bestS = inf;
    for(int i = d; i <= u; i++) {
        bestS = min(bestS, s[i][column] - i);
        bestE = min(bestE, e[i][column] - i);
        result = min(result, bestS + e[i][column] + i);
        result = min(result, bestE + s[i][column] + i);
        bestSV[i][column] = min(bestSV[i][column], bestS + i);
        bestEV[i][column] = min(bestEV[i][column], bestE + i);
    }
    bestS = inf, bestE = inf;
    for(int i = u; i >= d; i--) {
        bestS = min(bestS, s[i][column] + i);
        bestE = min(bestE, e[i][column] + i);
        result = min(result, bestS + e[i][column] - i);
        result = min(result, bestE + s[i][column] - i);
        bestSV[i][column] = min(bestSV[i][column], bestS - i);
        bestEV[i][column] = min(bestEV[i][column], bestE - i);
    }
    
    for(int i = d; i <= u; i++) {
        bestV[i][column] = result;
        visited[i][column] = true;
    }
        
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            if(grid[i][j] == 'P') {
                start = make_pair(i, j);
                grid[i][j] = '.';
            }
            if(grid[i][j] == 'K') {
                finish = make_pair(i, j);
                grid[i][j] = '.';
            }
            bestSV[i][j] = bestSH[i][j] = bestEV[i][j] = bestEH[i][j] = inf;
        }
    }
    for(int i = 0; i < n + 2; i++)
        grid[0][i] = grid[n + 1][i] = grid[i][0] = grid[i][n + 1] = 'X';
    
    BFS(start);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            s[i][j] = d[i][j];
            for(int k = 0; k < 4; k++) {
                int I = i + moves[k][0], J = j + moves[k][1];
                if(ValidTile(I, J)) {
                    s[i][j] = min(s[i][j], d[I][J] + 1);
                }
            }
        }
    }
    
    BFS(finish);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            e[i][j] = d[i][j];
            for(int k = 0; k < 4; k++) {
                int I = i + moves[k][0], J = j + moves[k][1];
                if(ValidTile(I, J)) {
                    e[i][j] = min(e[i][j], d[I][J] + 1);
                }
            }
        }
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(grid[i][j] != 'X' && !visited[i][j]) {
                CalcHorizontal(make_pair(i, j));
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            visited[i][j] = false;
        }
    }
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(grid[i][j] != 'X' && !visited[i][j]) {
                CalcVertical(make_pair(i, j));
            }
        }
    }
    
    pair<int, int>best = start;
    int bestResult = Check(start);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int result = Check(make_pair(i, j));
            if(result < bestResult) {
                best = make_pair(i, j);
                bestResult = result;
            }
        }
    }
    
    if(bestResult >= n * n * 4 + 100) {
        cout << "NIE\n";
        return 0;
    }
    
    cout << bestResult << '\n' << best.first << ' ' << best.second << '\n';
    
    Detonate(best);
    BFS(start);
    vector<char>c;
    for(pair<int, int>p = finish; p != start; p = parent[p.first][p.second]) {
        if(parent[p.first][p.second].first == p.first) {
            c.push_back(parent[p.first][p.second].second > p.second ? 'L' : 'P');
        } else {
            c.push_back(parent[p.first][p.second].first > p.first ? 'G' : 'D');
        }
    }
    
    while(!c.empty()) {
        cout << c.back();
        c.pop_back();
    }
    cout << '\n';
    
    
    return 0;
}
