#include <cstdio>
#include <vector>

using namespace std;

void pre_calc(int x, int p, vector<vector<int>>&adj, vector<int>&dp, vector<int>&my_add) {
    
    int children_count = 0;
    int non_zero_count = 0;
    for(int y : adj[x]) {
        if(y == p)
            continue;
        pre_calc(y, x, adj, dp, my_add);
        children_count++;
        if(dp[y] != 0)
            non_zero_count++;
        dp[x] += dp[y];
    }
    
    if(non_zero_count < children_count - 1) {
        my_add[x] = children_count - 1 - non_zero_count;
        dp[x] += my_add[x];
    }
}

void get_answer(int x, int p, vector<vector<int>>&adj, vector<int>&dp, vector<int>&my_add, int &result) {
    
    
    
    dp[x] = my_add[x] = 0;
    
    int children_count = 0;
    int non_zero_count = 0;
    for(int y : adj[x]) {
        children_count++;
        if(dp[y] != 0)
            non_zero_count++;
        dp[x] += dp[y];
    }
    
    if(non_zero_count < children_count - 1) {
        my_add[x] = children_count - 1 - non_zero_count;
        dp[x] += my_add[x];
    }
    
    result = min(result, dp[x] + 1);
    
    for(int y : adj[x]) {
        if(y == p)
            continue;
        dp[x] -= dp[y];
        if(children_count - non_zero_count > 1 && dp[y] == 0) {;
            dp[x]--;
            my_add[x]--;
        }
        get_answer(y, x, adj, dp, my_add, result);
        dp[x] += dp[y];
        if(children_count - non_zero_count > 1 && dp[y] == 0) {
            dp[x]++;
            my_add[x]++;
        }
    }
    
    if(p != -1) {
        dp[x] -= dp[p];
        if(children_count - non_zero_count > 1 && dp[p] == 0) {
            dp[x]--;
            my_add[x]--;
        }
    }
}

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<int>>adj(n);
    for(int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    
    vector<int>dp(n, 0), my_add(n, 0);
    pre_calc(0, -1, adj, dp, my_add);
    int result = n == 1 ? 0 : n;
    get_answer(0, -1, adj, dp, my_add, result);
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
