#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    vector<pair<int, int>>p;
    for(int i = 1; i < n; i++) {
        p.emplace_back(a[i] - a[i - 1], i);
    }
    
    sort(p.begin(), p.end());
    
    while(!p.empty() && p.back().first >= 0)
        p.pop_back();
    
    for(int i = 1; i <= n; i++) {
        if(p.empty()) {
            printf("1 ");
        } else {
            printf("%d ", p.back().second + 1);
            p.back().first += i;
            if(p.back().first >= 0)
                p.pop_back();
        }
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
