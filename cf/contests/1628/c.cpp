#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<vector<int>>grid(n, vector<int>(n));
    for(vector<int>&row : grid) {
        for(int &cell : row) {
            cin >> cell;
        }
    }
    
    if(n == 2) {
        cout << (grid[0][0] ^ grid[0][1]) << '\n';
        return;
    }
    int result = 0;
    
    if((n / 2) % 2 == 0) {
        int stepsAtTheBottom = ((n / 2) + 1) / 2;
        for(int row = 0; row < n / 2; row += 2) {
            for(int j = 0; j < stepsAtTheBottom - row / 2; j++) {
                result ^= grid[row][row + j * 4] ^ grid[row][row + j * 4 + 1];
                result ^= grid[n - row - 1][row + j * 4] ^ grid[n - row - 1][row + j * 4 + 1];
            }
        }
        
        int stepsAtTheLeft = (n - 4) / 4;
        for(int column = 0; column < n / 2 - 2; column += 2) {
            for(int j = 0; j < stepsAtTheLeft - column / 2; j++) {
                result ^= grid[3 + column + j * 4][column] ^ grid[3 + column + j * 4 + 1][column];
                result ^= grid[3 + column + j * 4][n - 3 - column] ^ grid[3 + column + j * 4 + 1][n - 3 - column];
            }
        }
        
        for(int i = 1; i < n; i += 4) {
            result ^= grid[i][n - 1] ^ grid[i + 1][n - 1];
        }
        
    } else {
        
        int stepsAtTheBottom = (n - 2) / 4;
        for(int row = 0; row < n / 2 - 2; row += 2) {
            for(int j = 0; j < stepsAtTheBottom - row / 2; j++) {
                result ^= grid[row][2 + row + j * 4] ^ grid[row][2 + row + j * 4 + 1];
                result ^= grid[n - 3 - row][2 + row + j * 4] ^ grid[n - 3 - row][2 + row + j * 4 + 1];
            }
        }
        
        int stepsAtTheLeft = (n - 2) / 4;
        for(int column = 0; column < n / 2; column += 2) {
            for(int j = 0; j < stepsAtTheLeft - column / 2; j++) {
                result ^= grid[1 + column + j * 4][column] ^ grid[1 + column + j * 4 + 1][column];
                result ^= grid[1 + column + j * 4][n - 1 - column] ^ grid[1 + column + j * 4 + 1][n - 1 - column];
            }
        }
        
        for(int i = 0; i < n; i += 4) {
            result ^= grid[n - 1][i] ^ grid[n - 1][i + 1];
        }
    }
    
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
