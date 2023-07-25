#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        a[i] = i;
    printf("%d\n", n);
    for(int i = 0; i < n; i++) {
        for(int x : a)
            printf("%d ", x + 1);
        printf("\n");
        if(i < n - 1)
            swap(a[i], a[i + 1]);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
