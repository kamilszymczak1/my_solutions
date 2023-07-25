#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cmath>
#include <cstring>

using namespace std;

int dist(pair<int, int>a, pair<int, int>b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

void test_case() {
    int max_x = 0, max_y = 0, min_x = 0, min_y = 0;
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        max_x = max(max_x, x);
        min_x = min(min_x, x);
        max_y = max(max_y, y);
        min_y = min(min_y, y);
    }
    vector<pair<int, int>>p;
    p.emplace_back(max_x, 0);
    p.emplace_back(min_x, 0);
    p.emplace_back(0, min_y);
    p.emplace_back(0, max_y);
    int result = 1 << 30;
    sort(p.begin(), p.end());
    do {
        int local = dist(make_pair(0, 0), p[0]);
        for(int i = 0; i < 3; i++)
            local += dist(p[i], p[i + 1]);
        local += dist(make_pair(0, 0), p.back());
        result = min(result, local);
    } while(next_permutation(p.begin(), p.end()));
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
