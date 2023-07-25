#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<bool>>grid(n, vector<bool>(n, false));
    if(n % 2 == 0) {
        for(int i = 0; 2 * i < n; i++) {
            grid[i][i * 2] = grid[i][i * 2 + 1] = 1;
            grid[i + n / 2][i * 2] = grid[i + n / 2][i * 2 + 1] = 1;
        }
        for(int i = 0; 2 * i < n - 2; i++) {
            grid[i + n / 2 + 1][i * 2] = 1;
            grid[n / 2 - 2 - i][n - 1 - i * 2] = 1;
        }
        grid[n / 2 - 1][1] = 1;
        grid[n / 2][n - 2] = 1;
        
    } else {
        
        for(int i = 0; 2 * i < n - 1; i++) {
            grid[i][i * 2] = grid[i][i * 2 + 1] = 1;
            grid[i + n / 2 + 1][i * 2 + 1] = grid[i + n / 2 + 1][i * 2 + 2] = 1;
        }
        
        for(int i = 0; 2 * i < n - 3; i++) {
            grid[i][2 * i + 3] = 1;
            grid[n / 2 + i][2 * i + 2] = 1;
        }
        grid[n - 2][n - 1] = 1;
        grid[n / 2 - 1][n - 1] = 1;
        grid[n / 2][0] = grid[n / 2][1] = 1;
        grid[n - 1][0] = 1;
    }
    
    
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << (grid[i][j] ? "#" : ".");
        }
        cout << '\n';
    }
    
    
    return 0;
}
