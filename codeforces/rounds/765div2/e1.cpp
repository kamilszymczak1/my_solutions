#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(vector<int>&init) {
        int _n = init.size();
        for(leafCount = 1; leafCount < _n; leafCount *= 2) {}
        values.resize(leafCount * 2, 1 << 30);
        for(int i = 0; i < _n; i++)
            values[i + leafCount] = init[i];
        for(int i = leafCount - 1; i; i--)
            values[i] = min(values[i * 2], values[i * 2 + 1]);
    }
    void Set(int x, int value) {
        values[x += leafCount] = value;
        for(x /= 2; x; x /= 2)
            values[x] = min(values[x * 2], values[x * 2 + 1]);
    }
    int GetMin(int a, int b) {
        int result = min(values[a += leafCount], values[b += leafCount]);
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result = min(result, values[a + 1]);
            if(b % 2 == 1)
                result = min(result, values[b - 1]);
            a /= 2; b /= 2;
        }
        return result;
    }
};

int Value(char c) {
    if(c == '(')
        return 1;
    return -1;
}
 
void TestCase() {
    int n, q; cin >> n >> q;
    string s; cin >> s;
    
    vector<int>pref(n + 1);
    for(int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + Value(s[i - 1]);
    }
    SegTree T(pref);
    
    stack<pair<int, int>>intervals;
    vector<int>lastAppearance(n * 2 + 7, n + 1);
    lastAppearance[pref[n] + n] = n;
    
    vector<vector<int>>next(n + 2), cnt(n + 2);
    vector<vector<long long>>ans(n + 2);
    
    for(int i = n - 1; i >= 0; i--) {
        int l = i + 1, r = lastAppearance[pref[i] + n];
        if(r <= n && T.GetMin(l, r) >= pref[i]) {
            if(!intervals.empty() && intervals.top().first < r) {
                ans[l].push_back(intervals.top().first - l);
                int count = 0;
                while(!intervals.empty() && intervals.top().first < r) {
                    count++;
                    ans[l][0] += ans[intervals.top().first][0] - 1;
                    intervals.pop();
                }
                ans[l][0] += (long long)count * (count + 1) / 2;
            } else {
                ans[l].push_back(1);
            }
            cnt[l].push_back(1);
            next[l].push_back(r + 1);
            intervals.push(make_pair(l, r));
        }
        
        lastAppearance[pref[i] + n] = i;
    }
    
    for(int i = n; i > 0; i--) {
        for(int j = 1; (int)next[i].size() == j && (int)next[next[i][j - 1]].size() >= j; j++) {
            int t = next[i][j - 1];
            next[i].push_back(next[t][j - 1]);
            cnt[i].push_back(cnt[i][j - 1] + cnt[t][j - 1]);
            ans[i].push_back(ans[i][j - 1] + ans[t][j - 1] + (long long)cnt[i][j - 1] * cnt[t][j - 1]);
        }
    }
    
    while(q--) {
        int t, a, b; cin >> t >> a >> b;
        long long thisAns = 0;
        int thisCnt = 0;
        for(int i = (int)next[a].size() - 1; i >= 0; i--) {
            if(i < (int)next[a].size() && next[a][i] <= b + 1) {
                thisAns = thisAns + ans[a][i] + (long long)thisCnt * cnt[a][i];
                thisCnt += cnt[a][i];
                a = next[a][i];
            }
        }
        cout << thisAns << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
