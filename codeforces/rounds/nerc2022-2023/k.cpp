#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<long long>>grid(n, vector<long long>(n));
    
    long long lo = 1ll << 60;
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%lld", &grid[i][j]);
            sum += grid[i][j];
            if((i == 0 && j == 0) || (i == n - 1 && j == n - 1))
                continue;
            lo = min(lo, grid[i][j]);
        }
    }
    printf("%lld\n", sum - lo);
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
