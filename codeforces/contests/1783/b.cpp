#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<int>>grid(n, vector<int>(n));
    int x = 1, b = n * n;
    int last = 0;
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            for(int j = 0; j < n; j++) {
                if(last == 0) {
                    grid[i][j] = x++;
                    last = 1;
                } else {
                    grid[i][j] = b--;
                    last = 0;
                }
            }
        } else {
            for(int j = n - 1; j >= 0; j--) {
                if(last == 0) {
                    grid[i][j] = x++;
                    last = 1;
                } else {
                    grid[i][j] = b--;
                    last = 0;
                }
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
