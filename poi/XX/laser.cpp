#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 500007, MAX_K = 107, BEG = 1, END = 0;
struct Point {
    int x, y, index;
    Point() {}
    Point(int _x, int _y, int _index) : x(_x), y(_y), index(_index) {}
};

Point p[MAX_N * 2];
int indexOf[MAX_N][2];
pair<int, int>segment[MAX_N * 2];
int dp[2][MAX_N * 2 + 7], amount[MAX_N * 2 + 7], last[MAX_N * 2 + 7], n, k;

bool cmp(Point a, Point b) {
    return (long long)a.x * b.y < (long long)a.y * b.x;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> k >> n;
    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        p[i * 2] = Point(x1, y1, i);
        p[i * 2 + 1] = Point(x2, y2, i);
    }
    sort(p, p + 2 * n, cmp);
    
    for(int i = 0; i < n; i++)
        indexOf[i][0] = indexOf[i][1] = -1;
    
    int lastIndex = 0;
    indexOf[p[0].index][0] = lastIndex;
    for(int i = 1; i < 2 * n; i++) {
        if(cmp(p[i - 1], p[i]))
            lastIndex++;
        if(indexOf[p[i].index][0] == -1)
            indexOf[p[i].index][0] = lastIndex;
        else
            indexOf[p[i].index][1] = lastIndex;
    }
    
    for(int i = 0; i < n; i++) {
        segment[i * 2] = make_pair(indexOf[i][0], indexOf[i][1] + 1);
        segment[i * 2 + 1] = make_pair(indexOf[i][1] + 1, indexOf[i][1] + 1);
    }
    
    sort(segment, segment + 2 * n);
    
    int _last = 0, _amount = 0, t = 0;
    for(int i = 0; i <= lastIndex; i++) {
        while(t < 2 * n && segment[t].first <= i) {
            if(segment[t].first < segment[t].second) {
                _last = max(_last, segment[t].second);
                _amount++;
            } else
                _amount--;
            t++;
        }
        last[i] = max(_last, i + 1);
        amount[i] = _amount;
    }
    
    for(int i = 0; i < k; i++) {
        for(int j = 0; j <= lastIndex; j++) {
            dp[1][last[j]] = max(dp[1][last[j]], dp[0][j] + amount[j]);
            dp[0][j + 1] = max(dp[0][j + 1], dp[0][j]);
        }
        for(int j = 0; j <= lastIndex + 1; j++)
            dp[0][j] = dp[1][j];
    }
    int result = 0;
    for(int i = 0; i <= lastIndex + 1; i++)
        result = max(result, dp[0][i]);
    cout << result << '\n';
    
    return 0;
}
