#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>c(n + 1);
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &c[i]);
        sum += c[i];
    }
    if(sum == 0) {
        for(int i = 0; i < n; i++)
            printf("0 ");
        printf("\n");
        return;
    }
    long long prefixOnes = sum / n;
    vector<long long>a(n + 1), suffixSum(n + 2);
    for(int i = n; i > 1; i--) {
         suffixSum[i] += suffixSum[i + 1];
         suffixSum[i] += 1;
         suffixSum[max(0ll, i - prefixOnes)] -= 1;
         
         if(c[i] != suffixSum[i]) {
             a[i] = 1;
             prefixOnes--;
        }
    }
    
    if(prefixOnes != 0)
        a[1] = 1;
    
    for(int i = 1; i <= n; i++)
        printf("%lld ", a[i]);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
