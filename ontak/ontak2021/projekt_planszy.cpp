#include <iostream>
#include <vector>

using namespace std;

long long f(long long x, long long width) {
    return width * (width + 1) * x * (x + 1) / 4 + 2 * x + 6;
}

void Color(int R, int C, int currentH, int width, vector<vector<bool>>&grid) {
    grid[R][C + 1] = grid[R][C + 2] = grid[R][C + width + 1] = 1;
    for(int i = 1; i <= currentH; i++)
        for(int j = 0; j < width; j++)
            grid[R + i][C + 2 + j] = 1;
}

vector<vector<bool>>GenGrid(const int K) {
    if(K == 2 || K == 4)
        return vector<vector<bool>>(0);
    vector<vector<bool>>grid;
    for(int width = 3; width <= 100; width++) {
        int k = K;
        bool done = true;
        const int n = 1000;
        grid = vector<vector<bool>>(n, vector<bool>(n, false));
        int R = 100, C = 100, currentH = 899;
        grid[R][C] = 1; k--;
        while(k >= 200 && C + width + 1 < 1000 && currentH >= 2) {
            while(k - f(currentH, width) >= 5 && C + width + 1 < 1000) {
                Color(R, C, currentH, width, grid);
                k -= f(currentH, width);
                C += width + 1;
            }
            currentH--;
        }
        R = 100, C = 100;
        if(k % 2 == 1) {
            grid[R - 1][C] = grid[R - 2][C] = 1;
            R -= 2;
            C--;
            k -= 5;
        } else {
            R--;
        }
        while(k > 0 && R >= 0 && K >= 0) {
            grid[R][C] = 1;
            if(grid[R + 1][C] == 1) {
                C--;
            } else {
                R--;
            }
            k -= 2;
        }
        if(k == 0)
            break;
    }

    return grid;
}

int main() {
    ios_base::sync_with_stdio(0);
    int k; cin >> k;
    vector<vector<bool>>grid = GenGrid(k);
    if(grid.empty()) {
        cout << "-1\n";
    } else {
        cout << "1000 1000\n";
        for(vector<bool>row : grid) {
            for(bool cell : row) {
                cout << (cell ? '#' : '.');
            }
            cout << '\n';
        }
    }
    
    return 0;
}
