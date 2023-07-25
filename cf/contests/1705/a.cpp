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
    int x; scanf("%d", &x);
    vector<int>a(2 * n);
    for(int &y : a)
        scanf("%d", &y);
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) {
        if(a[i + n] - a[i] < x) {
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
    return 0;
}
