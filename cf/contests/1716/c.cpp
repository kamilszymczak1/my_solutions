#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

long long solve(vector<vector<long long>>&a, int bottom) {
    
    int m = a[0].size();
    long long result = 1ll << 60;
    
    vector<long long>right_time(m), left_time(m);
    
    right_time[m - 1] = a[bottom][m - 1];
    for(int i = m - 2; i >= 0; i--)
        right_time[i] = max(right_time[i + 1], a[bottom][i] + m - i - 1);
    
    left_time[m - 1] = a[bottom ^ 1][m - 1];
    for(int i = m - 2; i >= 0; i--)
        left_time[i] = max(left_time[i + 1] + 1, a[bottom ^ 1][i]);
    
    long long elapsed_time = a[bottom][0];
    for(int i = 0; i < m; i++) {
        long long right_arrival = max(elapsed_time + m - i - 1, right_time[i]);
        long long left_arrival = max(right_arrival + m - i, left_time[i]);
        
        result = min(result, left_arrival);
        
        if((i + bottom) % 2 == 0) {
            elapsed_time = max(elapsed_time + 1, a[bottom ^ 1][i]);
            if(i + 1 < m) {
                elapsed_time = max(elapsed_time + 1, a[bottom ^ 1][i + 1]);
                elapsed_time = max(elapsed_time + 1, a[bottom][i + 1]);
            }
        } else {
            if(i + 1 < m) {
                elapsed_time = max(elapsed_time + 1, a[bottom][i + 1]);
            }
        }
        
    }
    
    result = min(result, elapsed_time);
    
    return result;
    
}

void test_case() {
    int m; scanf("%d", &m);
    vector<vector<long long>>grid(2, vector<long long>(m));
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%lld", &grid[i][j]);
            grid[i][j]++;
        }
    }
    grid[0][0] = 0;
    long long result = min(solve(grid, 1), solve(grid, 0));
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
