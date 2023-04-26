#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <bitset>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    long long result = 0, value = a[0];
    long long changed = 0;
    for(int i = 1; i < n; i++) {
        result += abs(a[i] - changed - value);
        if(a[i] - changed > value) {
            changed += abs(a[i] - changed - value);
        } else {
            value -= abs(a[i] - changed - value);
        }
        
    }
    result += abs(value);
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
