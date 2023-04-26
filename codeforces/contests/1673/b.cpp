#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>

using namespace std;

char c[200007];

void TestCase() {
    scanf("%s", c);
    int n = strlen(c);
    set<char>chars;
    for(int i = 0; i < n; i++)
        chars.insert(c[i]);
    if(chars.size() == 1) {
        printf("YES\n");
        return;
    }
    int all = chars.size();
    for(int i = 0; i < all; i++) {
        auto it = chars.find(c[i]);
        if(it != chars.end()) {
            chars.erase(it);
        }
    }
    
    if(chars.size() > 0) {
        printf("NO\n");
        return;
    }
    for(int i = 1; i < n / all; i++) {
        for(int j = 0; j < all; j++) {
            if(c[(i - 1) * all + j] != c[i * all + j]) {
                printf("NO\n");
                return;
            }
        }
    }
    int last = (n / all) * all;
    for(int i = 0; i + last < n; i++) {
        if(c[i + last] != c[i + last - all]) {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
