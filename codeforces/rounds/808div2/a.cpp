#include <cstdio>

using namespace std;

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int n; scanf("%d", &n);
        bool result = true;
        int f; scanf("%d", &f);
        for(int i = 1; i < n; i++) {
            int x; scanf("%d", &x);
            if(x % f != 0)
                result = false;
        }
        printf("%s\n", result ? "YES" : "NO");
    }
    return 0;
}
