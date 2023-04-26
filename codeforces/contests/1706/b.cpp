#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<vector<int>>v(n);
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        v[x - 1].emplace_back(i);
    }
    
    for(int i = 0; i < n; i++) {
        vector<int>dp(2);
        for(int x : v[i]) {
            dp[x % 2] = max(dp[x % 2], dp[1 - x % 2] + 1);
        }
        printf("%d ", max(dp[0], dp[1]));
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
