#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef unsigned long long uint64;

uint64 Sqrt(uint64 n) {
    uint64 a = 0, b = (1ull << 32) - 1;
    while(a <= b) {
        uint64 m = (a + b) >> 1;
        if(m * m <= n) {
            a = m + 1;
        } else {
            b = m - 1;
        }
    }
    return a - 1;
}

void TestCase() {
    uint64 n; scanf("%llu", &n);
    if(n <= 3) {
        printf("1\n");
        return;
    }
    vector<uint64>v(1, n);
    while(v.back() != 1)
        v.push_back(Sqrt(v.back()));
    vector<vector<uint64>>dp(v.size());
    dp.back().resize(2);
    dp.back()[1] = 1;
    for(int i = (int)v.size() - 2; i >= 2; i--) { 
        dp[i].resize(v[i] + 1, 0);
        for(int j = 1; j <= (int)v[i + 1]; j++)
            dp[i + 1][j] += dp[i + 1][j - 1];
        
        for(int j = 1; j <= (int)v[i]; j++)
            dp[i][j] = dp[i + 1][Sqrt(j)];
    }
    uint64 result = 0, sqrtN = Sqrt(n);
    for(uint64 i = 1; i <= v[2]; i++)
        result += dp[2][i] * (sqrtN - i * i + 1);
    printf("%llu\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
