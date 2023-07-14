#include <cstdio>
#include <vector>
#include <algorithm>
    
using namespace std;
    
void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    sort(a.begin(), a.end());
    for(int i = 1; i < n; i++) {
        if((a[i] & a[0]) != a[0]) {
            printf("-1\n");
            return;
        }
    }
    printf("%d\n", n * 2);
    for(int i = 0; i < n; i++)
        printf("%d %d ", a[i], a[0]);
    printf("\n");
}
    
int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
