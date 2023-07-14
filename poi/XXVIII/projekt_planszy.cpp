#include <iostream>

using namespace std;

const int MAX_N = 107;
char grid[MAX_N][MAX_N];

void Brute4(long long k) {
    int n = 100;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            grid[i][j] = '#';
        }
    }
    for(int i = 0; i < 25; i++) {
        int row = i * 4, collumn = i * 2;
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 3; k++) {
                grid[row + j][collumn + k] = '.';
            }
        }
    }
    for(int i = 0; k; i++, k /= 10) {
        int row = i * 4, collumn = i * 2;
        fill(grid[row] + collumn, grid[row] + n - 2, '.');
        int y = k % 10;
        fill(grid[row + 1] + n - 2 - y, grid[row + 1] + n, '.');
    }
    for(int i = 0; i < n; i++)
        grid[i][n - 1] = '.';
    cout << n << '\n';
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}
int main() {
    long long k;
    cin >> k;
    Brute4(k);
    return 0;
}
