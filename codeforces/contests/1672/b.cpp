#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>

using namespace std;

const int MAX_N = 200007;
char c[MAX_N];

void TestCase() {
    scanf("%s", c);
    int n = strlen(c);
    bool ans = true, b = false;
    if(c[0] == 'B' || c[n - 1] != 'B')
        ans = false;
    int count = 0;
    for(int i = 0; i < n; i++) {
        b |= c[i] == 'B';
        count += c[i] == 'A' ? 1 : -1;
        if(count < 0)
            ans = false;
    }
    if(b == false)
        ans = false;
    printf("%s\n", ans ? "YES" : "NO");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
