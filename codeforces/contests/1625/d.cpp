#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int>result;

int bitLen(int x) { return x == 0 ? 0 : (32 - __builtin_clz(x)); }

void Get(int k, vector<pair<int, int>>&a) {
    vector<vector<pair<int, int>>>bucket(31);
    for(auto &[x, id] : a)
        bucket[bitLen(x)].emplace_back(x, id);
    vector<pair<int, int>>smaller;
    if(!bucket[0].empty())
        smaller.push_back(bucket[0][0]);
    bool done = false;
    for(int i = 0; i <= 30; i++) {
        if(bucket[i].empty())
            continue;
        sort(bucket[i].begin(), bucket[i].end());
        if((1 << i) - 1 < k) {
            for(pair<int, int>p : bucket[i])
                smaller.push_back(p);
        } else if(k >= (1 << (i - 1))) {
            for(auto [x, id] : bucket[i]) {
                for(int firstDiff = 0; firstDiff < i; firstDiff++) {
                    if(((1 << firstDiff) & (k - 1)) != 0)
                        continue;
                    int smallestPossible = ((((x ^ (k - 1)) >> (firstDiff + 1)) << 1) ^ ((x >> firstDiff) & 1) ^ 1) << firstDiff;
                    int ind = lower_bound(smaller.begin(), smaller.end(), make_pair(smallestPossible, -1)) - smaller.begin();
                    if(!smaller.empty() && ind != smaller.size() && (smaller[ind].first ^ x) >= k) {
                        result.push_back(id);
                        result.push_back(smaller[ind].second);
                        done = true;
                        break;
                    }  
                }
                if(done)
                    break;
            }
            smaller.push_back(bucket[i][0]);
        } else {
            for(auto &[x, id] : bucket[i])
                x ^= (1 << (i - 1));
            Get(k, bucket[i]);
        }
    }
    if(!done && smaller.size() != 0)
        result.push_back(smaller[0].second);
}

void TestCase() {
    int n, k; cin >> n >> k;
    if(k == 0 && n >= 2) {
        cout << n << '\n';
        for(int i = 0; i < n; i++)
            cout << i + 1 << ' ';
        cout << '\n';
        return;
    }
    vector<pair<int, int>>a;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a.emplace_back(x, i + 1);
    }
    Get(k, a);
    if(result.size() < 2) {
        cout << "-1\n";
    } else {
        cout << result.size() << '\n';
        for(int x : result)
            cout << x << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
