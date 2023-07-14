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
    set<pair<int, int>>s;
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    if(n % 2 != 0) {
        printf("-1\n");
        return;
    }
    
    vector<pair<int, int>>seg;
    for(int i = 0; i < n; i += 2) {
        if(a[i] == a[i + 1]) {
            seg.emplace_back(i + 1, i + 2);
        } else {
            seg.emplace_back(i + 1, i + 1);
            seg.emplace_back(i + 2, i + 2);
        }
    }
    
    printf("%d\n", (int)seg.size());
    for(auto [a, b] : seg)
        printf("%d %d\n", a, b);
    
    
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
