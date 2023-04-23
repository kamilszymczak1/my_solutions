#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    reverse(a.begin(), a.end());
    int sum_p = 0;
    if(a[0] == a[1])
        swap(a[0], a[n - 1]);
    for(int i = 0; i < n; i++) {
        if(a[i] == sum_p) {
            printf("NO\n");
            return;
        }
        sum_p += a[i];
    }
    printf("YES\n");
    for(int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
