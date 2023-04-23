#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;

void TestCase() {
    set<int>s;
    int n; scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        s.insert(n / i);
    printf("%d\n", (int)s.size());
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
