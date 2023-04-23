#include <iostream>
#include <vector>

using namespace std;

void TestCase1() {
    int n; cin >> n;
    if(n > 4) {
        cout << "NIE\n";
    } else {
        cout << "TAK\n";
        if(n == 1) {
            cout << "1 1 1 2\n";
        }
        if(n == 2) {
            cout << "1 1 2 1\n3 1 3 2\n1 2 2 2\n";
        }
        if(n == 3) {
            cout << "1 1 2 1\n3 1 3 2\n4 1 5 1\n1 2 2 2\n4 2 5 2\n6 1 6 2\n";
        }
        if(n == 4) {
            cout << "2 4 3 4\n2 2 2 1\n2 3 1 3\n3 3 4 3\n3 1 3 2\n1 1 1 2\n4 1 4 2\n1 4 1 5\n2 5 3 5\n4 4 4 5\n";
        }
    }
}

void FillVertical(int a, int b, int column, vector<vector<int>>&grid, int &currentBlock) {
    for(int i = a; i <= b; i++) {
        grid[i][column] = currentBlock;
        if((i - a) % 3 == 2)
            currentBlock++;
    }
}

void FillHorizontal(int a, int b, int row, vector<vector<int>>&grid, int &currentBlock) {
    for(int i = a; i <= b; i++) {
        grid[row][i] = currentBlock;
        if((i - a) % 3 == 2)
            currentBlock++;
    }
}

void TestCase2() {
    int n, m, a, b; cin >> n >> m >> a >> b;
    int up = n - a, down = a - 1, left = b - 1, right = m - b;
    if(n % 3 != m % 3 || n % 3 == 0 || !(up % 3 == down % 3 && down % 3 == left % 3 && left % 3 == right % 3) || up % 3 == 1) {
        cout << "NIE\n";
        return;
    }
    vector<vector<int>>grid(n, vector<int>(m, 0));
    int currentBlock = 1;
    if(up % 3 == 0) {
        for(int i = 0; i < n; i++) {
            FillHorizontal(0, b - 2, i, grid, currentBlock);
            FillHorizontal(b, m - 1, i, grid, currentBlock);
        }
        FillVertical(0, a - 2, b - 1, grid, currentBlock);
        FillVertical(a, n - 1, b - 1, grid, currentBlock);
    } else {
        for(int i = 0; i < a - 1; i++)
            FillHorizontal(0, b - 1, i, grid, currentBlock);
        for(int i = a; i < n; i++)
            FillHorizontal(b - 1, m - 1, i, grid, currentBlock);
        for(int i = 0; i < b - 1; i++)
            FillVertical(a - 1, n - 1, i, grid, currentBlock);
        for(int i = b; i < m; i++)
            FillVertical(0, a - 1, i, grid, currentBlock);
    }
    
    cout << "TAK\n";
    for(vector<int>&row : grid) {
        for(int i = 0; i < m - 1; i++)
            cout << row[i] << ' ';
        cout << row[m - 1] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int q, t; cin >> q >> t;
    if(q == 1) {
        while(t--)
            TestCase1();
    } else {
        while(t--)
            TestCase2();
    }
    
    return 0;
}
