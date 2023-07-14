#include <cstdio>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a) {
        scanf("%d", &x);
        x--;
    }
    
    vector<vector<bool>>deletable(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++) {
        vector<int>count(n);
        int top = -1, size = 0;
        for(int j = i; j < n; j++) {
            count[a[j]]++;
            if(size == 0 || top == a[j]) {
                top = a[j];
                size++;
            } else {
                size--;
            }
            
            if((j - i + 1) % 2 == 0 && (size == 0 || count[top] * 2 <= j - i + 1))
                deletable[i][j] = true;
        }
    }
    
    vector<int>dp(n, -(1 << 30));
    for(int i = 0; i < n; i++) {
        
        if(i != 0 && a[i] == a[i - 1])
            dp[i] = max(dp[i], dp[i - 1] + 1);
        
        if(i == 0 || deletable[0][i - 1])
            dp[i] = max(dp[i], 1);
        
        for(int j = i - 2; j > 0; j -= 2) {
            if(deletable[j][i - 1] && a[i] == a[j - 1]) {
                dp[i] = max(dp[i], dp[j - 1] + 1);
            }
        }
    }
    
    int result = max(0, dp[n - 1]);
    for(int i = 0; i < n - 1; i++) {
        if(deletable[i + 1][n - 1]) {
            result = max(result, dp[i]);
        }
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
