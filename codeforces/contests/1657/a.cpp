#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

void TestCase() {
    int x, y; scanf("%d%d", &x, &y);
    
    if(x == 0 && y == 0) {
        printf("0\n");
        return;
    }
    int z = x * x + y * y;
    double t = round(sqrt(z));
    if(t * t == z) {
        printf("1\n");
    } else {
        printf("2\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
