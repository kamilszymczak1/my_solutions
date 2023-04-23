#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n, k, r, c; scanf("%d%d%d%d", &n, &k, &r, &c);
    r--; c--;
    
    vector<vector<char>>grid(n, vector<char>(n, '.'));
    
    int row = r, col = c;
    do {
        
        int my_row = row;
        do {
            grid[my_row][col] = 'X';
            my_row = (my_row + k) % n;
        } while(my_row != row);
        
        col = (col + 1) % n;
        row = (row + 1) % n;
    } while(row != r);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            printf("%c", grid[i][j]);
        printf("\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
