#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

const int T = 333, MAX_N = 100'007;
int m[MAX_N * 2 * (T + 3)];

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    int result = min(2, n);
    for(int i = -T; i <= T; i++) {
        for(int j = 0; j < n; j++)
            result = max(result, ++m[a[j] - j * i + n * T]);
        for(int j = 0; j < n; j++)
            m[a[j] - j * i + n * T]--;
    }
    vector<map<int, int>>dp(n);
    for(int i = 0; i < n; i++) {
        for(int j = i - 1; j >= max(0, i - MAX_N / T + 1); j--) {
            int t = abs(a[i] - a[j]);
            if(t % (i - j) != 0)
                continue;
            int r = (a[i] - a[j]) / (i - j);
            if(dp[j].find(r) != dp[j].end()) {
                result = max(result, dp[i][r] = max(dp[i][r], dp[j][r] + 1));
            } else {
                dp[i][r] = max(dp[i][r], 2);
            }
        }
    }
    
    printf("%d\n", n - result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
}
