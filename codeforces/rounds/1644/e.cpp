#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Rect {
    long long x1, y1, x2, y2;
    Rect(int _x1, int _y1, int _x2, int _y2) {
        x1 = _x1;
        y1=  _y1;
        x2 = _x2;
        y2 = _y2;
    }
    long long Area() {
        long long x = (x2 - x1 + 1);
        long long y = (y2 - y1 + 1);
        return x * y;
    }
};

void TestCase() {
    int n; cin >> n;
    string s; cin >> s;
    int m = s.size();
    vector<pair<int, int>>suff(m + 1, make_pair(0, 0));
    int dCnt = 0, rCnt = 0;
    for(int i = (int)s.size() - 1; i >= 0; i--) {
        suff[i] = suff[i + 1];
        if(s[i] == 'D') {
            dCnt++;
            suff[i].second++;
        } else {
            rCnt++;
            suff[i].first++;
        }
    }
    
    if(dCnt == 0 || rCnt == 0) {
        cout << n << '\n';
        return;
    }
    int j = 0;
    vector<Rect>r;
    int x = 0, y = 0;
    long long result = 0;
    while(s[0] == s[j]) {
        if(s[j] == 'D')
            y++;
        if(s[j] == 'R')
            x++;
        j++;
    }
    result += j + 1;
    while(j <= m) {
        pair<int, int>toGo = suff[j];
        int x1 = x, y1 = y;
        int x2 = n - toGo.first - 1, y2 = n - toGo.second - 1;
        r.emplace_back(x1, y1, x2, y2);
        if(j < m && s[j] == 'D')
            y++;
        if(j < m && s[j] == 'R')
            x++;
        j++;
    }
    reverse(r.begin(), r.end());
    long long lastX = n + 1, lastY = n + 1;
    for(Rect R : r) {
        long long A = R.Area();
        long long X = R.x2 - max(R.x1, lastX) + 1;
        long long Y = R.y2 - max(R.y1, lastY) + 1;
        result += A - X * Y;
        lastX = R.x1;
        lastY = R.y1;
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
