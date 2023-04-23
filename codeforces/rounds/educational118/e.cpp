#include <cstdio>
#include <vector>

using namespace std;

char c[1'000'007];

int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<char>>grid(n + 2, vector<char>(m + 2, '#'));
    
    pair<int, int>source = make_pair(0, 0);
    for(int i = 1; i <= n; i++) {
        scanf("%s", c);
        for(int j = 1; j <= m; j++) {
            grid[i][j] = c[j - 1];
            if(c[j - 1] == 'L')
                source = make_pair(i, j);
        }
    }
    
    vector<vector<int>>adj_count(n + 2, vector<int>(m + 2));
    vector<vector<int>>goo_count(n + 2, vector<int>(m + 2));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(grid[i][j] != '#') {
                for(int k = 0; k < 4; k++) {
                    int I = i + moves[k][0], J = j + moves[k][1];
                    
                    if(grid[I][J] != '#') {
                        adj_count[i][j]++;
                    }
                }
            }
        }
    }
    
    vector<vector<bool>>visited(n + 2, vector<bool>(m + 2));
    
    vector<pair<int, int>>q;
    q.push_back(source);
    visited[source.first][source.second] = true;
    
    while(!q.empty()) {
        
        auto [i, j] = q.back(); q.pop_back();
        
        grid[i][j] = '+';
        for(int k = 0; k < 4; k++) {
            int I = i + moves[k][0], J = j + moves[k][1];
            
            if(grid[I][J] != '#' && !visited[I][J]) {
                goo_count[I][J]++;
                
                if(adj_count[I][J] - goo_count[I][J] <= 1) {
                    visited[I][J] = true;
                    q.emplace_back(I, J);
                }
            }
        }
        
    }
    
    grid[source.first][source.second] = 'L';
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
