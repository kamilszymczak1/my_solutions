#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int &x : a)
        scanf("%d", &x);
    for(int &x : b)
        scanf("%d", &x);
    
    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]) {
            if(a[i] > b[i]) {
                printf("NO\n");
                return;
            }
            
            //a[i] < b[i]
            
            //we want to make a[i] = b[i]
            //so we want a[i + 1] to be at least b[i] - 1
            
            if(b[(i + 1) % n] < b[i] - 1) {
                printf("NO\n");
                return;
            }
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
