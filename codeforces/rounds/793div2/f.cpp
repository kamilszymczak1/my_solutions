#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <bitset>

using namespace std;

char c[200007];

void TestCase() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    int l = 0, r = 0, result = 0;
    if(n % 2 == 1) {
        l = r = n / 2;
        result = 1;
    } else {
        l = n / 2 - 1;
        r = n / 2;
        if(c[l] != c[r]) {
            printf("0\n");
            return;
        }
        result = 2;
    }
    while(l > 0 && c[l - 1] == c[r + 1]) {
        l--;
        r++;
        result += 2;
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
