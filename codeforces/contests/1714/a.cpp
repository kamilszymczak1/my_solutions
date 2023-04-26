#include <cstdio>
#include <algorithm>

using namespace std;

void test_case() {
    int n, H, M; scanf("%d%d%d", &n, &H, &M);
    int T = H * 60 + M;
    int result = 1 << 30;
    for(int i = 0; i < n; i++) {
        int h, m; scanf("%d%d", &h, &m);
        int t = h * 60 + m;
        if(t >= T)
            result = min(result, t);
        else
            result = min(result, t + 24 * 60);
    }
    result -= T;
    printf("%d %d\n", result / 60, result % 60);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
