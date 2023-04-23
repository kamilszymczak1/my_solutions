#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

void TestCase() {
    char s[50];
    scanf("%s", s);
    char c;
    do {
        c = getchar();
    } while(!('a' <= c && c <= 'z'));
    int n = strlen(s);
    bool flag = false;
    for(int i = 0; i < n; i++) {
        if(s[i] == c) {
            int left = i, right = n - i - 1;
            if(left % 2 == 0 && right % 2 == 0) {
                printf("YES\n");
                return;
            }
        }
    }
    printf("NO\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
