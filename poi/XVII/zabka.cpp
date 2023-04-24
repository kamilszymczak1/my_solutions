#include <cstdio>
#include <vector>

using namespace std;

long long D(long long a, long long b) {
    if(a < b)
        return b - a;
    return a - b;
}

const int MAX_N = 1'000'007;
int jump[MAX_N], a[MAX_N][2], t = 0;
long long p[MAX_N];

void Calc(long long m, int n) {
    if(m == 0) {
        for(int i = 0; i < n; i++)
            a[i][0] = i;
        return;
    }
    Calc(m / 2, n);
    t ^= 1;
    for(int i = 0; i < n; i++)
        a[i][t] = a[a[i][t ^ 1]][t ^ 1];
    if(m % 2 == 1) {
        t ^= 1;
        for(int i = 0; i < n; i++)
            a[i][t] = a[jump[i]][t ^ 1];
    }
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    long long m; scanf("%lld", &m);
    for(int i = 0; i < n; i++)
        scanf("%lld", &p[i]);
    int beg = 0;
    for(int i = 0; i < n; i++) {
        while(beg + k + 1 < n && D(p[beg], p[i]) > D(p[beg + k + 1], p[i]))
            beg++;
        jump[i] = D(p[beg], p[i]) >= D(p[beg + k], p[i]) ? (beg) : (beg + k);
    }
    
    Calc(m, n);
    for(int i = 0; i < n; i++)
        printf("%d ", a[i][t] + 1);
    printf("\n");
}
