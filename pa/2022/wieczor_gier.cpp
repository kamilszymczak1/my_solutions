#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <cassert>

using namespace std;

const int MAX_N = 8;

const int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int grid[MAX_N][MAX_N];
long long choose[MAX_N * MAX_N + 1][MAX_N * MAX_N + 1];
int n, m, k, a_parity = 0, b_parity = 0;

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] == 'O') {
                a_parity = (a_parity + i + j) % 2;
            }
        }
    }
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            if(s[j] == 'O') {
                grid[i][j] = 1;
                k++;
                b_parity = (b_parity + i + j) % 2;
            }
        }
    }
    
    int moves_count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] != 1)
                continue;
            for(int t = 0; t < 4; t++) {
                int x = i + moves[t][0];
                int y = j + moves[t][1];
                if(x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 1) {
                    moves_count++;
                }
            }
        }
    }
    
    if(a_parity != b_parity) {
        cout << "0\n";
        return 0;
    }
    
    for(int i = 0; i < MAX_N * MAX_N; i++) {
        choose[i][0] = choose[i][i] = 1;
        for(int j = 1; j < min(MAX_N + 1, i); j++) {
            choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
        }
    }
    
    long long all = (2 * n * m - (m + n)) * choose[n * m - 2][k - 1];
    
    long double answer = moves_count / (long double)all;
    cout << fixed << setprecision(15) << answer << '\n';
    
    
    
    return 0;
}
