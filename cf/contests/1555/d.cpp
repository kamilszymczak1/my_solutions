#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<string>perm = {"abc", "acb", "bac", "bca", "cab", "cba"};
    vector<vector<vector<int>>>cost(n + 1, vector<vector<int>>(6, vector<int>(3, 0)));
    
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 6; j++) {
            for(int k = 0; k < 3; k++) {
                cost[i][j][k] = cost[i - 1][j][k] + (perm[j][(i + k) % 3] != s[i - 1]);
            }
        }
    }
    
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        int result = n + 10;
        for(int j = 0; j < 6; j++) {
            for(int k = 0; k < 3; k++) {
                result = min(result, cost[b][j][k] - cost[a - 1][j][k]);
            }
        }
        cout << result << '\n';
    }
    
    return 0;
}
