#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    vector<pair<long long, long long>>p(3);
    for(int i = 0; i < 3; i++) {
        cin >> p[i].first >> p[i].second;
    }
    long long result = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                if(i == j || i == k || j == k)
                    continue;
                if(p[i].second == p[j].second && p[k].second < p[i].second) {
                    result += abs(p[i].first - p[j].first);
                }
            }
        }
    }
    cout << result / 2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
