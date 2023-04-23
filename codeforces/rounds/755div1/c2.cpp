#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<long long>a(n);
    for(long long &x : a)
        scanf("%lld", &x);
    
    long long result = 0;
    for(int i = 0; i < n; i++) {
        long long l = a[i];
        for(int j = i + 1; j < n; j++) {
            l = a[j] - l;
            if(l < 0)
                break;
            if(l == 0) {
                printf("%d %d\n", i, j);
                result++;
            }
        }
    }
    printf("total coutn = %lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
