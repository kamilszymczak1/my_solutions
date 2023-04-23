#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    int total_sum = 0;
    vector<int>a(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        total_sum += a[i];
    }
    
    if(abs(total_sum) % 2 == 1) {
        printf("-1\n");
        return;
    }
    
    map<int, int>prefix[2];
    int pref[2] = {0, 0};
    prefix[0][0] = prefix[1][0] = 0;
    vector<int>parent(n + 1, -1);
    for(int i = 1; i <= n; i++) {
        int j = i & 1;
        pref[j ^ 0] += a[i];
        pref[j ^ 1] -= a[i];
        
        //we take even number of elements
        if(prefix[j ^ 0].find(pref[j ^ 1]) != prefix[j ^ 0].end()) {
            parent[i] = prefix[j ^ 0].find(pref[j ^ 1]) -> second;
        }
        
        //we take an odd number of elements
        if(prefix[j ^ 1].find(pref[j ^ 0]) != prefix[j ^ 1].end()) {
            parent[i] = prefix[j ^ 1].find(pref[j ^ 0]) -> second;
        }
        
        if()
    }
    
    if(parent[n] == -1) {
        printf("-1\n");
        return;
    }
    
    vector<pair<int, int>>seg;
    for(int i = n; i != -1; i++) {
        seg.emplace_back(parent[i] + 1, i);
    }
    reverse(seg.begin(), seg.end());
    for(auto [a, b] : seg)
        printf("%d %d\n", a, b);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
