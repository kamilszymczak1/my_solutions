#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int &x : a)
        scanf("%d", &x);
    for(int &x : b)
        scanf("%d", &x);
    
    vector<int>mx(n), mn(n);
    
    vector<int>next_right(n), next_left(n);
    next_right[n - 1] = n - 1;
    for(int i = n - 2; i >= 0; i--) {
        if(a[i + 1] <= b[i]) {
            next_right[i] = next_right[i + 1];
        } else {
            next_right[i] = i;
        }
        mx[i] = b[next_right[i]] - a[i];
    }
    mx[n - 1] = b[n - 1] - a[n - 1];
    
    mn[0] = b[0] - a[0];
    
    for(int i = 1; i < n; i++) {
        if(a[i - 1] <= b[i]) {
            next_left[i] = next_left[i - 1];
        } else {
            next_left[i] = i;
        }
        mn[i] = b[next_left[i]] - a[i];
        if(mn[i] < 0)
            mn[i] = *lower_bound(b.begin(), b.end(), a[i]) - a[i];
    }
    
    for(int x : mn)
        printf("%d ", x);
    printf("\n");
    
    for(int x : mx)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
