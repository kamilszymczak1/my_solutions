#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>p(n);
    for(int i = 0; i < n; i++)
        p[i] = i;
    int count = 0;
    do {
        vector<int>q(n);
        for(int i = 0; i < n; i++)
            q[p[i]] = i;
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if(abs(p[i] - q[i]) > 1) {
                ok = false;
            }
        }
        
        if(ok) {
            count++;
//             printf("p = ");
//             for(int x : p)
//                 printf("%d ", x + 1);
//             printf("\n");
        }
    } while(next_permutation(p.begin(), p.end()));
    printf("count = %d\n", count);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
