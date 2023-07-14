#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<vector<long long>>grid(2 * n, vector<long long>(2 * n, 0));
    for(int i = 0; i < 2 * n; i++) {
        for(int j = 0; j < 2 * n; j++) {
            cin >> grid[i][j];
        }
    }
    long long normalCost = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            normalCost += grid[i + n][j + n];
        }
    }
    long long result = min(grid[n][n - 1], grid[n - 1][n]);
    result = min(result, grid[0][2 * n - 1]);
    result = min(result, grid[2 * n - 1][0]);
    result = min(result, grid[0][n]);
    result = min(result, grid[n][0]);
    result = min(result, grid[2 * n - 1][n - 1]);
    result = min(result, grid[n - 1][2 * n - 1]);
    
    
    cout << normalCost + result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
