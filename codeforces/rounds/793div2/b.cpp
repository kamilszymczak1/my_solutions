#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <bitset>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>p(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    int x = 0;
    while(p[x] == x)
        x++;
    for(int i = 0; i < n; i++) {
        if(p[i] != i) {
            if((x & p[i]) != x) {
                //x is not a submask of p[i]
                x = x & p[i];
            }
        }
    }
    printf("%d\n", x);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
