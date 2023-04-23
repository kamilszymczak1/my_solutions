#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;


int moves[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

vector<pair<int, int>> Neighbours(int x, int y, int n, int m) {
    vector<pair<int, int>>ans;
    for(int i = 0; i < 4; i++) {
        int X = x + moves[i][0], Y = y + moves[i][1];
        if(X < 0 || X >= n || Y < 0 || Y >= m)
            continue;
        ans.emplace_back(X, Y);
    }
    return ans;
}

bool Problematic(int x, int y, vector<vector<int>>&grid, int n, int m) {
    for(int i = 0; i < 4; i++) {
        int X = x + moves[i][0], Y = y + moves[i][1];
        if(X < 0 || X >= n || Y < 0 || Y >= m)
            continue;
        if(grid[x][y] > grid[X][Y])
            return false;
    }
    return true;
}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<int>>grid(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    pair<int, int>problematic = {-1, -1};
    int problematicCount = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(Problematic(i, j, grid, n, m)) {
                problematicCount++;
                if(grid[i][j] != 1) {
                    problematic = make_pair(i, j);
                }
            }
        }
    }
    
    if(problematicCount == 1) {
        printf("0\n");
        return 0;
    }
    
    //problematicCount > 0
    auto toMove = Neighbours(problematic.first, problematic.second, n, m);
    toMove.emplace_back(problematic.first, problematic.second);
    
    vector<pair<int, int>>v;
    
    for(auto [x, y] : toMove) {
        auto B = Neighbours(x, y, n, m);
        B.emplace_back(x, y);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                auto A = Neighbours(i, j, n, m);
                A.emplace_back(i, j);
                A.insert(A.end(), B.begin(), B.end());
                sort(A.begin(), A.end());
                A.resize(unique(A.begin(), A.end()) - A.begin());
                
                for(auto [x2, y2] : A)
                    problematicCount -= Problematic(x2, y2, grid, n, m);
                swap(grid[x][y], grid[i][j]);
                for(auto [x2, y2] : A)
                    problematicCount += Problematic(x2, y2, grid, n, m);
                if(problematicCount == 1) {
                    v.emplace_back(x * m + y, i * m + j);
                    if(v.back().first > v.back().second)
                        swap(v.back().first, v.back().second);
                }
                    
                for(auto [x2, y2] : A)
                    problematicCount -= Problematic(x2, y2, grid, n, m);
                swap(grid[x][y], grid[i][j]);
                for(auto [x2, y2] : A)
                    problematicCount += Problematic(x2, y2, grid, n, m);
            }
        }
    }
    
    sort(v.begin(), v.end());
    v.resize(unique(v.begin(), v.end()) - v.begin());
    
    if(v.size() == 0) {
        printf("2\n");
    } else {
        printf("1 %d\n", (int)v.size());
    }
    
    return 0;
}
