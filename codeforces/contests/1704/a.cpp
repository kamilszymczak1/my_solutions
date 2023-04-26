#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

char a[100'000], b[100'000];

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    scanf("%s%s", a, b);
    bool answer = true;
    for(int i = 1; i < m; i++) {
        if(b[i] != a[n - m + i])
            answer = false;
    }
    if(answer) {
        bool answer2 = false;
        for(int i = 0; i <= n - m; i++)
            if(a[i] == b[0])
                answer2 = true;
            
            if(answer2)
                printf("YES\n");
            else
                printf("NO\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
