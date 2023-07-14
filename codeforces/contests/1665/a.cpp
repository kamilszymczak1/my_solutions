#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    printf("%d %d %d %d\n", n - 3, 1, 1, 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
