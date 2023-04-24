#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>

using namespace std;

char c[5000];

void TestCase() {
    scanf("%s", c);
    int n = strlen(c);
    bool ok = true;
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && c[i] == c[j])
            j++;
        int len = j - i;
        if(len == 1)
            ok = false;
        i = j - 1;
    }
    if(ok) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
