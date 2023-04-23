#include <iostream>

using namespace std;
const int MAX_N = 1000007;
char a[MAX_N];
int p[3][MAX_N], n;

int Get(char c) {
    return c == 'S' ? 0 : (c == 'C' ? 1 : 2);
}

bool Good(int i, int j) {
    int x = p[0][j] - p[0][i - 1];
    int y = p[1][j] - p[1][i - 1];
    int z = p[2][j] - p[2][i - 1];
    return x != y  && x != z && y != z || (x == y && x == 0 ) || (x == z && x == 0) || (y == z && y == 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    scanf("%d%s", &n, &a);
    for(int i = n; i > 0; i--)
        a[i] = Get(a[i - 1]);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 3; j++)
            p[j][i] += p[j][i - 1];
        p[a[i]][i]++;
    }
    
    int result = 0;
    for(int i = 1; i <= 3; i++) {
        for(int j = i; j <= n; j++) {
            if(Good(i, j)) {
                result = max(result, j - i + 1);
            }
        }
        for(int j = 1; j <= n - i + 1; j++) {
            if(Good(j, n - i + 1)) {
                result = max(result, n - i - j + 2);
            }
        }
    }
    cout << result << '\n';
    return 0;
}
