#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 100'007;

long long Calc(vector<int>&x) {
    if(x.empty())
        return 0;
    sort(x.begin(), x.end());
    int n = x.size();
    long long result = 0;
    long long rightCount = n;
    long long totalDistToRight = 0;
    for(int i = 1; i < n; i++)
        totalDistToRight += x[i] - x[0];
    for(int i = 0; i < n; i++) {
        result += totalDistToRight;
        rightCount--;
        if(i < n - 1)
            totalDistToRight -= (x[i + 1] - x[i]) * rightCount;
    }
    return result;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<vector<int>>inRow(MAX_N), inColumn(MAX_N);
    //vector<int>grid(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int c; cin >> c;
            inRow[c - 1].push_back(j);
            inColumn[c - 1].push_back(i);
        }
    }
    
    long long result = 0;
    for(int i = 0; i < MAX_N; i++)
        result += Calc(inRow[i]) + Calc(inColumn[i]);
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    
    return 0;
}
