#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    if(n == 1) {
        printf("1\n 1 1\n");
        return;
    }
    printf("%d\n", n - 1);
    for(int i = 1; i <= n - 1; i++)
        printf("%d %d\n", i, i);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
