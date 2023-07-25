#include <algorithm>
#include <vector>
#include <iostream>
#include <bitset>

using namespace std;

const long long inf = 1ll << 60;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>>spices(1 << n);
    for(int i = 1; i < (1 << n); i++) {
        int cost; cin >> cost;
        spices.emplace_back(cost, i);
    }
    sort(spices.begin(), spices.end());
    vector<bool>achievable(1 << n, false);
    achievable[0] = true;
    long long result = 0;
    for(auto [cost, spice] : spices) {
        if(!achievable[spice]) {
            result += cost;
            vector<int>newAchievable;
            for(int i = 0; i < (1 << n); i++) {
                if(achievable[i] && !achievable[i ^ spice]) {
                    newAchievable.push_back(i ^ spice);
                }
            }
            for(int x : newAchievable)
                achievable[x] = true;
        }
    }
    cout << result << '\n';
    return 0;
}
