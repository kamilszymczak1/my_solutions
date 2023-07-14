#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>>grid(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            char c; cin >> c;
            grid[i][j] = c == '#' ? 1 : 0;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n - 6; j++) {
            int sumA = 0, sumB = 0;
            for(int k = 0; k < 6; k++) {
                sumA += grid[i][j + k];
                sumB += grid[j + k][i];
            }
            if(sumA >= 4 || sumB >= 4) {
                cout << "Yes\n";
                return 0;
            }
        }
    }
    
    for(int i = 0; i <= n - 6; i++) {
        for(int j = 0; j <= n - 6; j++) {
            int sumA = 0, sumB = 0;
            for(int k = 0; k < 6; k++) {
                sumA += grid[i + k][j + k];
                sumB += grid[i + k][j + 5 - k];
            }
            if(sumA >= 4 || sumB >= 4) {
                cout << "Yes\n";
                return 0;
            }
        }
    }
    cout << "No\n";
    
    return 0;
}
