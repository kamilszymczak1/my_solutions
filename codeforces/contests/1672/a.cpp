#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    int cuts = 0;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        cuts += x - 1;
    }
    printf("%s\n", cuts % 2 == 0 ? "maomao90" : "errorgorn");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
