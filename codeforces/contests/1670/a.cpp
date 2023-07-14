#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <map>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    int negative = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        negative += a[i] < 0;
        a[i] = abs(a[i]);
    }
    for(int i = 0; i < negative - 1; i++) {
        if(a[i] < a[i + 1]) {
            printf("NO\n");
            return;
        }
    }
    for(int i = negative; i < n - 1; i++) {
        if(a[i] > a[i + 1]) {
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
}
