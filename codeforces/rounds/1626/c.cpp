#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long H(pair<long long, long long>&a) {
    return a.second - a.first + 1;
}

void TestCase() {
    int n; cin >> n;
    vector<long long>k(n + 1), h(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> k[i];
    for(int i = 1; i <= n; i++)
        cin >> h[i];
    vector<pair<long long, long long>>segments;
    segments.emplace_back(1, 1);
    for(int i = 1; i <= n; i++) {
        long long need = h[i];
        while(H(segments.back()) + k[i] - segments.back().second < need) {
            segments.pop_back();
        }
        long long diffX = k[i] - segments.back().second;
        if(diffX >= need) {
            segments.emplace_back(k[i] - need + 1, k[i]);
        } else {
            segments.back().second = k[i];
        }
    }
    long long result = 0;
    if(segments[0] == make_pair(1ll, 1ll) && k[1] != 1)
        result--;
    for(auto [a, b] : segments) {
        long long len = b - a + 1;
        result += len * (len + 1) / 2;
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
