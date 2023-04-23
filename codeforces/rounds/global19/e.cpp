#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

void TestCase() {
    int n, m; cin >> n >> m;
    map<int, int>cnt;
    map<int, vector<int>>f;
    map<pair<int, int>, bool>bad;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt[x]++;
        bad[make_pair(x, x)] = true;
    }
    for(auto [value, count] : cnt)
        f[count].push_back(value);
    
    for(int i = 0; i < m; i++) {
        long long x, y; cin >> x >> y;
        bad[make_pair(x, y)] = true;
        bad[make_pair(y, x)] = true;
    }
    long long result = 0;
    for(auto [value, count] : cnt) {
        for(auto &[count2, vec] : f) {
            if(count2 > count)
                break;
            int i = (int)vec.size() - 1;
            while(i >= 0 && bad[make_pair(value, vec[i])])
                i--;
            if(i >= 0) {
                long long x = (long long)(value + vec[i]) * (count + count2);
                result = max(result, x);
            }
        }
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
