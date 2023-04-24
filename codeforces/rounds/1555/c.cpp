#include <iostream>
#include <vector>

using namespace std;

const long long inf = 1e9 + 7;

void TestCase() {
    int m; cin >> m;
    vector<vector<int>>a(2, vector<int>(m));
    for(vector<int>&b : a) {
        for(int &c : b) {
            cin >> c;
        }
    }
    vector<int>sumTopRight(m + 1);
    sumTopRight[m] = 0;
    for(int i = m - 1; i >= 0; i--)
        sumTopRight[i] = sumTopRight[i + 1] + a[0][i];
    vector<int>sumDownLeft(m + 1);
    sumDownLeft[0] = 0;
    for(int i = 1; i <= m; i++)
        sumDownLeft[i] = sumDownLeft[i - 1] + a[1][i - 1];
    
    int result = inf;
    for(int i = 0; i < m; i++) {
        result = min(result, max(sumTopRight[i + 1], sumDownLeft[i]));
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
