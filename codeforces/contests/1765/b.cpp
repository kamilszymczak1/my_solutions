#include <cstdio>
#include <cstring>

using namespace std;

char c[200];

void test_case() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    
    if(n % 3 == 2) {
        printf("NO\n");
        return;
    }
    
    for(int i = 0; i < n / 3; i++) {
        int a = 3 * i + 1;
        int b = 3 * i + 2;
        
        if(c[a] != c[b]) {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
