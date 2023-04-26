#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct Move {
    int x1, y1, x2, y2;
    Move(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<bool>>grid(n, vector<bool>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; do c = getchar(); while(c != '0' && c != '1');
            grid[i][j] = c - '0';
        }
    }
    if(grid[0][0] == 1) {
        printf("-1\n");
        return;
    }
    vector<vector<bool>>grid2(n, vector<bool>(m));
    vector<Move>moves;
    for(int i = n - 1; i >= 0; i--) {
        for(int j = m - 1; j; j--) {
            if(grid[i][j]) {
                moves.emplace_back(i, j - 1, i, j);
            }
        }
    }
    for(int i = n - 1; i; i--) {
        if(grid[i][0]) {
            moves.emplace_back(i - 1, 0, i, 0);
        }
    }
    printf("%d\n", (int)moves.size());
    for(Move move : moves)
        printf("%d %d %d %d\n", move.x1 + 1, move.y1 + 1, move.x2 + 1, move.y2 + 1);
    
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
