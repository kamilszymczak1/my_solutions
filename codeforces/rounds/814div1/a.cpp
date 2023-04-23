#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>
#include <bitset>

using namespace std;

int ceil(int a, int b) {
    int c = a / b;
    if(c * b == a)
        return c;
    return c + 1;
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>v(n);
    for(int &a : v)
        scanf("%d", &a);
    
    vector<vector<pair<int, int>>>states(2);
    
    states[0].emplace_back(0, 0);
    for(int i = 0; i < n; i++) {
        states[1].clear();
        int best_cost = 1 << 30;
        for(auto [cost, value] : states[0]) {
            if(value == 0) {
                //I have removed the previous one already
                states[1].emplace_back(cost, v[i]);
                best_cost = min(best_cost, cost);
            } else {
                states[1].emplace_back(cost + 1, v[i] ^ value);
                best_cost = min(best_cost, cost + 1);
            }
        }
        states[1].emplace_back(best_cost + 1, 0);
        swap(states[0], states[1]);
    }
    
    int result = 1 << 30;
    
    for(auto [cost, value] : states[0]) {
        if(value == 0)
            result = min(result, cost);
        else
            result = min(result, cost + 1);
    }
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
