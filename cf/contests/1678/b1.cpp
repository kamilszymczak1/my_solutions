#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 300'007;
const int inf = 1 << 30;

char c[MAX_N];

void test_case() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    vector<int>dp(2, 1);
    int operations = 0;
    for(int i = 0; i < n; i += 2) {
        vector<int>new_dp(2, inf);
        if(c[i] != c[i + 1]) {
            operations++;
            new_dp[0] = min(dp[0], dp[1] + 1);
            new_dp[1] = min(dp[1], dp[0] + 1);
        } else {
            int t = c[i] - '0';
            new_dp[t] = min(dp[t], dp[t ^ 1] + 1);
        }
        swap(dp, new_dp);
    }
    
    printf("%d\n", operations);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
