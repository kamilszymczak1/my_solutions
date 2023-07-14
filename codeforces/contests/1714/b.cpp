#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a) {
        scanf("%d", &x);
        x--;
    }
    
    vector<bool>flag(n);
    for(int i = n - 1; i >= 0; i--) {
        if(flag[a[i]]) {
            printf("%d\n", i + 1);
            return;
        }
        flag[a[i]] = true;
    }
    printf("0\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
