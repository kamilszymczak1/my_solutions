#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    
    if(n % 2 == 0) {
        for(int i = n - 2; i >= 1; i--)
            printf("%d ", i);
        printf("%d %d\n", n - 1, n);
    } else {
        printf("1 ");
        for(int i = n - 2; i > 1; i--)
            printf("%d ", i);
        printf("%d %d\n", n - 1, n);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
