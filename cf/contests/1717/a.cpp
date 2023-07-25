#include <cstdio>

using namespace std;

void test_case() {
    long long n; scanf("%lld", &n);
    
    long long result = n;
    
    result += (n / 2) * 2;
    result += (n / 3) * 2;
    
    
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}

