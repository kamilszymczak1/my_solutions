#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;

bool Sgn(int x) {
    if(x < 0)
        return -1;
    return 1;
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
    
    long long result = 0;
    vector<int>a(2);
    for(int i = 0; i < n; i++) {
        
        for(int j = 0; j < 2; j++) {
            result += abs(a[j]);
            a[j] += grid[0][j][i] - grid[1][j][i];
        }
        
        for(int j = 0; j < 2; j++) {
            while(a[j] > 0 && a[j ^ 1] < 0) {
                a[j]--;
                a[j ^ 1]++;
                result++;
            }
        }
    }
    
    
    printf("%lld\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
