#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

const long long MAX_N = 1e9 + 7;

long long r(vector<long long>&a) {
    int n = a.size();
    vector<bool>appear(n * (n - 1) / 2 + 10, false);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[j] - a[i] < appear.size()) {
                appear[a[j] - a[i]] = true;
            }
        }
    }
    int result = 1;
    while(appear[result])
        result++;
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    vector<long long>a = {1, 2};
    
    while(a.back() - a[a.size() - 2] <= MAX_N) {
        if(a.size() & 1) {
            a.push_back(a.back() + r(a));
        } else {
            a.push_back(a.back() * 2);
        }
    }
    a.pop_back();
    
    map<long long, pair<int, int>>m;
    vector<long long>diffs;
    for(int i = 0; i < a.size(); i++) {
        for(int j = i + 1; j < a.size(); j++) {
            m[a[j] - a[i]] = {j + 1, i + 1};
            diffs.emplace_back(a[j] - a[i]);
        }
    }
    sort(diffs.begin(), diffs.end());
    
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(m[x] != make_pair(0, 0)) {
            cout << m[x].first << ' ' << m[x].second << '\n';
        } else {
            m.erase(x);
            long long smallerInDiffs = lower_bound(diffs.begin(), diffs.end(), x) - diffs.begin();
            long long result = 2 * (x - smallerInDiffs) + 55;
            cout << result + 1 << ' ' << result << '\n';
        }
    }
    
    return 0;
}
