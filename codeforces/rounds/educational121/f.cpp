#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const long long mod = 998244353;

inline void Add(int &a, long long b) {
    a = (a + b) % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, a, x, y, k, M;
    cin >> n >> a >> x >> y >> k >> M;
    int s = k * (k - 1) / 2 + 1, result = 0;
    vector<vector<int>>sum(2, vector<int>(s, 0)), count(2, vector<int>(s, 0));
    vector<int>nonZero(s);
    vector<bool>taken(s, false);
    for(int z = 0; z < n; z++) {
        count[0][0] = 1;
        int bound = min(s, a + 1), nonZeroSize = 1;
        taken[0] = true;
        for(int i = 1; i <= k; i++) {
            int t = nonZeroSize;
            for(int l = 0; l < t; l++) {
                int j = nonZero[l];
                long long currentValue = a - j;
                int newDecrease = j + (currentValue % i);
                Add(count[1][newDecrease], count[0][j]);
                Add(sum[1][newDecrease], currentValue * count[0][j] + sum[0][j]);
                if(!taken[newDecrease]) {
                    taken[newDecrease] = true;
                    nonZero[nonZeroSize++] = newDecrease;
                }
                Add(count[1][j], 1ll * count[0][j] * (n - 1));
                Add(sum[1][j], 1ll * sum[0][j] * (n - 1));
            }
            swap(count[0], count[1]);
            swap(sum[0], sum[1]);
            for(int l = 0; l < t; l++) {
                int j = nonZero[l];
                count[1][j] = sum[1][j] = 0;
            }
        }
        for(int l = 0; l < nonZeroSize; l++) {
            int i = nonZero[l];
            Add(result, sum[0][i]);
            taken[i] = false;
            count[0][i] = sum[0][i] = 0;
        }
        a = (1ll * a * x + y) % M;
    }
    cout << result << '\n';
    
    return 0;
}
