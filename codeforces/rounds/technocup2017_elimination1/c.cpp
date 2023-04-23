#include <cstdio>
#include <vector>

using namespace std;

int query(int a, int b) {
    printf("? %d %d\n", a + 1, b + 1);
    fflush(stdout);
    int x; scanf("%d", &x);
    return x;
}

int main() {
    int n; scanf("%d", &n);
    vector<int>k;
    for(int i = 0; i < n - 1 + n % 2; i++)
        k.push_back(query(i, (i + 1) % (n - 1 + n % 2)));
    
    vector<int>a(n);
    for(int i = 0; i < (int)k.size(); i++)
        a[0] += (1 - 2 * (i % 2)) * k[i];
    a[0] /= 2;
    for(int i = 1; i < (int)k.size(); i++)
        a[i] = k[i - 1] - a[i - 1];
    if(n % 2 == 0)
        a[n - 1] = query(0, n - 1) - a[0];
    printf("! ");
    for(int x : a)
        printf("%d ", x);
    printf("\n");
    
    return 0;
}
