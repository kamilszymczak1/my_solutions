#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>

using namespace std;

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    
    if(n > m) {
        printf("NO\n");
        return;
    }
    
    vector<int>a(n, 1);
    
    if(n % 2 == 1) {
        a[0] = m - n + 1;
    } else if(m % 2 == 0){
        a[0] = (m - n + 2) / 2;
        a[1] = (m - n + 2) / 2;
    } else {
        printf("NO\n");
        return;
    }
    
    printf("YES\n");
    for(int x : a)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
