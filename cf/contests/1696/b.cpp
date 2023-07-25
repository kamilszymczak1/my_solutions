#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>zeroes;
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(a[i] == 0)
            zeroes.push_back(i);
    }
    
    if(zeroes.empty()) {
        printf("1\n");
        return;
    }
    
    if(zeroes.size() == n) {
        printf("0\n");
        return;
    }
    
    int l = 0;
    while(l < n && a[l] == 0)
        l++;
    int r = n - 1;
    while(r >= 0 && a[r] == 0)
        r--;
    
    int zeroes_border = l + n - 1 - r;
    
    if(zeroes_border == zeroes.size()) {
        printf("1\n");
        return;
    }
    printf("2\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
