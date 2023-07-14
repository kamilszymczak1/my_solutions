#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAX_N = 200007;
int PI[MAX_N], border[MAX_N];
char type[MAX_N];
void CalcPI(int a, int b) {
    int t = PI[a - 1];
    for(int i = a; i <= b; i++) {
        while(t >= 0 && type[i] != type[t + 1])
            t = PI[t];
        PI[i] = ++t;
    }
}

void Query() {
    scanf("%s", &type);
    int n = strlen(type);
    for(int i = n; i > 0; i--)
        type[i] = type[i - 1];
    CalcPI(1, n);
    int x = n, r = 0;
    while(x > 0) {
        border[r++] = x;
        x = PI[x];
    }
    reverse(border, border + r);
    for(int i = 1; i <= border[0]; i++)
        type[i] = '0';
    if(border[0] != 1)
        type[border[0]] = '1';
    CalcPI(1, border[0]);
    for(int i = 1; i < r; i++) {
        int diff = border[i] - border[i - 1] * 2;
        if(diff <= 0) {
            for(int j = 2 * border[i - 1] - border[i] + 1; j <= border[i - 1]; j++) {
                type[j + border[i] - border[i - 1]] = type[j];
            }
            CalcPI(border[i - 1] + 2, border[i]);
        } else {
            int s = border[i] - 2 * border[i - 1];
            for(int j = 1; j <= s; j++)
                type[j + border[i - 1]] = '0';
            CalcPI(border[i - 1] + 1, s + border[i - 1]);
            int c = PI[s + border[i - 1]];
            if(c > 0 && ((s + border[i - 1]) % (s + border[i - 1] - c) == 0)) {// pierwotny
                type[s + border[i - 1]] = '1';
                CalcPI(s + border[i - 1], s + border[i - 1]);
            }
            for(int j = border[i - 1] + s + 1; j <= border[i]; j++) {
                type[j] = type[j - border[i - 1] - s];
            }
            CalcPI(border[i - 1] + s + 1, border[i]);
        }
    }
    for(int i = 1; i <= n; i++)
        printf("%c", type[i]);
    printf("\n");
}
int main() {
    PI[0] = -1;
    int T;
    scanf("%d", &T);
    while(T--)
        Query();
    return 0;
}

/*
 3
 ABIABUABIAB
 BABBAB
 BABURBAB
 */
