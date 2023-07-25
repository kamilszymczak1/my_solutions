#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a, b;
    int k1 = n, k2 = n;
    int i = 0, j = 1;
    while(k1 > 0) {
        a.push_back(i + 1);
        k1 -= i + 1;
        i = 1 - i;
    }
    while(k2 > 0) {
        b.push_back(j + 1);
        k2 -= j + 1;
        j = 1 - j;
    }
    
    if(k2 == 0) {
        for(int x : b)
            printf("%d", x);
    } else {
        for(int x : a)
            printf("%d", x);
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
