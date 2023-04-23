#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;

char c[100007], s[100007];

void TestCase() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    for(int i = 0; i <= n; i++)
        s[i] = 1;
    reverse(c, c + n);
    for(int i = 0; i < n; i++)
        c[i] -= '0';
    for(int i = 0; i <= n; i++) {
        if(c[i] > s[i]) {
            s[i + 1]--;
            s[i] += 10;
        }
        s[i] -= c[i];
    }
    if(s[n] != 0 || s[n - 1] == 0) {
        s[0] = s[n] = 1;
        for(int i = 1; i < n; i++)
            s[i] = 0;
        for(int i = 0; i <= n; i++) {
            if(c[i] > s[i]) {
                s[i + 1]--;
                s[i] += 10;
            }
            s[i] -= c[i];
        }
    }
    for(int i = 0; i < n; i++)
            s[i] += '0';
    reverse(s, s + n);
    printf("%s\n", s);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
