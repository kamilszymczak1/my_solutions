#include <cstdio>
#include <vector>

using namespace std;

int n, m;

bool on_grid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int moves[8][2] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

char c[100'000];

void test_case() {
    scanf("%d%d", &n, &m);
    vector<vector<int>>v(n, vector<int>(m));
    int sum = 0;
    for(int i = 0; i < n; i++) {
        scanf("%s", c);
        for(int j = 0; j < m; j++) {
            v[i][j] = c[j] - '0';
            sum += v[i][j];
        }
    }
    
    int zeroes = n * m - sum;
    if(zeroes == 0) {
        printf("%d\n", n * m - 2);
        return;
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(v[i][j] == 0) {
                for(int k = 0; k < 8; k++) {
                    int I = i + moves[k][0], J = j + moves[k][1];
                    
                    if(on_grid(I, J) && v[I][J] == 0) {
                        printf("%d\n", sum);
                        return;
                    }
                }
            }
        }
    }
    
    printf("%d\n", sum - 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        test_case();
    }
}
