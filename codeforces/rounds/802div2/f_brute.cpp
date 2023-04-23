#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;

const long long inf = 1ll << 60;

int D(int a, int b) {
    if(a % 2 == b % 2)
        return abs(a / 2 - b / 2);
    return abs(a / 2 - b / 2) + 1;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<vector<vector<int>>>grid(2, vector<vector<int>>(2, vector<int>(n)));
    vector<int>cnt(2, 0);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < n; k++) {
                scanf("%d", &grid[i][j][k]);
                cnt[i] += grid[i][j][k];
            }
        }
    }
    
    if(cnt[0] != cnt[1]) {
        printf("-1\n");
        return;
    }
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[0][i][j] == grid[1][i][j]) {
                grid[0][i][j] = grid[1][i][j] = 0;
            }
        }
    }
    
    vector<int>a, b;
    for(int i = 0; i < 2 * n; i++) {
        if(grid[0][i % 2][i / 2] + grid[1][i % 2][i / 2] == 1) {
            if(grid[0][i % 2][i / 2])
                a.push_back(i);
            if(grid[1][i % 2][i / 2])
                b.push_back(i);
        }
        
    }
    long long result = inf;
    do {
        long long local = 0;
        for(int i = 0; i < (int)a.size(); i++)
            local += D(a[i], b[i]);
        if(local < result) {
//             printf("b = ");
//             for(int x : b)
//                 printf("%d ", x);
//             printf("\n");
        } else if(local == result) {
//             printf("(equal) b = ");
//             for(int x : b)
//                 printf("%d ", x);
//             printf("\n");
        }
        result = min(result, local);
    } while(next_permutation(b.begin(), b.end()));
    printf("%lld\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
