#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<long long>a(n);
    for(auto &x : a)
        scanf("%lld", &x);
    long long sum = 0;
    for(int i = 0; i < n - 1; i++)
        sum += a[i];
    
    if(sum == 0) {
        printf("0\n");
        return;
    }
    int i = 0;
    while(a[i] == 0)
        i++;
    while(i < n - 1) {
        sum += a[i] == 0;
        i++;
    }
    printf("%lld\n", sum);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
