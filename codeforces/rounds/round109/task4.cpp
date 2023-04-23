#include <iostream>
#include <vector>

using namespace std;

const int inf = 1 << 30;

vector<int>freeChairs;
vector<int>occupiedChairs;
int n;

int dp[5007][5007];

int move(int current, int target) {
    return abs(occupiedChairs[current - 1] - freeChairs[target - 1]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(x == 0) {
            freeChairs.push_back(i);
        } else {
            occupiedChairs.push_back(i);
        }
    }
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = inf;
        }
    }
    
    dp[0][0] = 0;
    
    for(int i = 0; i <= occupiedChairs.size(); i++) {
        for(int j = 0; j <= freeChairs.size(); j++) {
            if(i > 0 && j > 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + move(i, j));
            }
            if(j > 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1]);
            }
        }
    }
    
    int result = inf;
    for(int i = 0; i <= n; i++) {
        result = min(dp[occupiedChairs.size()][i], result);
    }
    
    cout << result << '\n';
    return 0;
}
