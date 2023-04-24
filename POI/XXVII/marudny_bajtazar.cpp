#include <cstdio>
using namespace std;
const int MAX_N = 100007, LOG = 17;
int different[MAX_N], count[LOG][MAX_N];
char a[MAX_N];

int max(int a, int b) {return a > b ? a : b;}
int min(int a, int b) {return a < b ? a : b;}

int query() {
    for(int i = 1; i < LOG; i++)
        if(different[i] < (1 << i))
            return i;
    return LOG;
}
int getHash(int beg, int end) {
    int result = 0;
    for(int i = beg; i <= end; i++)
        result = (result << 1) + a[i];
    return result;
}

void addHash(int level, int hash) {
    if(count[level][hash] == 0)
        different[level]++;
    count[level][hash]++;
}

void removeHash(int level, int hash) {
    if(count[level][hash] == 1)
        different[level]--;
    count[level][hash]--;
}

void preprocessing(int n) {
    scanf("%s", &a);
    for(int i = n; i > 0; i--)
        a[i] = a[i - 1] - '0';
    for(int i = 1; i < LOG; i++)
        for(int j = 1; j + i - 1 <= n; j++)
            addHash(i, getHash(j, j + i - 1));
}

void flip(int x, int n) {
    int r = min(n, x + LOG - 2);
    for(int i = 1; i < LOG; i++)
        for(int j = max(1, x - i + 1); j + i - 1 <= r; j++)
            removeHash(i, getHash(j, j + i - 1));
    a[x] = 1 - a[x];
    for(int i = 1; i < LOG; i++)
        for(int j = max(1, x - i + 1); j + i - 1 <= r; j++)
            addHash(i, getHash(j, j + i - 1));
}

int main() {
    int n, q, x;
    scanf("%d%d", &n, &q);
    preprocessing(n);
    printf("%d\n", query());
    while(q--) {
        scanf("%d", &x);
        flip(x, n);
        printf("%d\n", query());
    }
    return 0;
}
