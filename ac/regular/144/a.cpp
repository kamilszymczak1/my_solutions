#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    printf("%d\n", 2 * n);
    vector<int>v;
    int x = n;
    while(x > 0) {
        int t = min(x, 4);
        v.emplace_back(t);
        x -= t;
    }
    for(int i = (int)v.size() - 1; i >= 0; i--)
        printf("%d", v[i]);
    printf("\n");
}
