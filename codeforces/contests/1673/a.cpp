#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>

using namespace std;

char s[200007];

void TestCase() {
    scanf("%s", s);
    int n = strlen(s);
    if(n == 1) {
        printf("Bob %d\n", s[0] - 'a' + 1);
        return;
    }
    printf("Alice ");
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += s[i] - 'a' + 1;
    if(n % 2 == 0) {
        printf("%d\n", sum);
    } else {
        sum -= 2 * min(s[0] - 'a' + 1, s[n - 1] - 'a' + 1);
        printf("%d\n", sum);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
