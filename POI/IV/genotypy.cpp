#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;

const int MAX_L = 107, A = 26, inf = 101;

int rules[A][A];
int dp[MAX_L][MAX_L], dpS[MAX_L];
char s[MAX_L];

int Query() {
    int n = strlen(s);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    
    for(int i = 0; i < n; i++)
        dp[i][i] = 1 << (s[i] - 'A');
    
    for(int len = 1; len < n; len++) {
        for(int i = 0; i + len < n; i++) {
            for(int j = i; j < i + len; j++) {
                for(int a = 0; a < A; a++) {
                    if(dp[i][j] & (1 << a)) {
                        for(int b = 0; b < A; b++) {
                            if(dp[j + 1][i + len] & (1 << b)) {
                                dp[i][i + len] |= rules[a][b];
                            }
                        }
                    }
                }
            }
        }
    }
    fill(dpS, dpS + MAX_L, inf);
    for(int i = 0; i < n; i++) {
        if(dp[0][i] & (1 << ('S' - 'A'))) {
            dpS[i] = 1;
        } else {
            for(int j = 1; j <= i; j++) {
                if(dp[j][i] & (1 << ('S' - 'A'))) {
                    dpS[i] = min(dpS[i], dpS[j - 1] + 1);
                }
            }
        }
    }
    return dpS[n - 1];
}

int main() {
    int n, k;
    scanf("%d", &n);
    char x, y, z;
    while(n--) {
        getchar();
        x = getchar(); y = getchar(); z = getchar();
        rules[y - 'A'][z - 'A'] |= 1 << (x - 'A');
    }
    scanf("%d", &k);
    while(k--) {
        scanf("%s", &s);
        int result = Query();
        if(result == inf) {
            printf("NIE\n");
        } else {
            printf("%d\n", result);
        }
    }
    
    return 0;
}
