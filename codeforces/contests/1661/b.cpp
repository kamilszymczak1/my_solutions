#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        int result = 30;
        for(int j = 0; j < 16; j++) {
            if(a == 0)
                result = min(result, j);
            else
                result = min(result, 15 - __builtin_ctz(a) + j);
            a = (a + 1) & ((1 << 15) - 1);
        }
        printf("%d ", result);
    }
    printf("\n");
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
