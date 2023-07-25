#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int MAX_N = 16;
bool freeRow[MAX_N + 1];
int n, a[MAX_N + 1][MAX_N + 1];

int A(int x, int y) {
    if(y < x)
        swap(x, y);
    return a[x][y];
}

int Get(int column, int res) {
    if(column == 2 * n + 1)
        return res;
    if(!freeRow[column])
        return Get(column + 1, res);
    freeRow[column] = false;
    int result = 0;
    for(int i = 1; i <= 2 * n; i++) {
        if(freeRow[i]) {
            freeRow[i] = false;
            result = max(result, Get(column + 1, res ^ A(i, column)));
            freeRow[i] = true;
        }
    }
    freeRow[column] = true;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    fill(freeRow, freeRow + 2 * n + 1, true);
    for(int i = 1; i < 2 * n; i++) {
        for(int j = i + 1; j <= 2 * n; j++) {
            cin >> a[i][j];
        }
    }
    cout << Get(1, 0) << '\n';
    
    return 0;
}
