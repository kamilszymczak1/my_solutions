#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

int is_there(int l, int r) {
    printf("? %d %d\n", l + 1, r);
    fflush(stdout);
    int outside_swaps = 0, inside_swaps = 0;
    for(int i = 0; i < r - l; i++) {
        int x; scanf("%d", &x); x--;
        if(l <= x && x < r) {
            inside_swaps++;
        } else {
            outside_swaps++;
        }
    }
    if(inside_swaps % 2 == 0)
        return false;
    return true;
}

int search(int l, int r) {
    if(r - l == 1)
        return l;
    int mid = (l + r) / 2;
    if(is_there(l, mid))
        return search(l, mid);
    return search(mid, r);
}

void test_case() {
    int n; scanf("%d", &n);
    printf("! %d\n", search(0, n) + 1);
    fflush(stdout);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
