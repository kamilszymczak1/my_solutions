#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>x(n);
    int oneCnt = 0, zeroCnt = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
        oneCnt += x[i] == 1;
        zeroCnt += x[i] == 0;
    }
    if(oneCnt != 0 && zeroCnt != 0) {
        printf("NO\n");
        return;
    }
    
    if(oneCnt == 0) { //there are no ones
        printf("YES\n");
        return;
    } else { //there are no zeroes
        sort(x.begin(), x.end());
        for(int i = n - 1; i >= 0; i--) {
            int j = i;
            while(j >= 0 && x[j] == x[i])
                j--;
            if(j >= 0 && x[j] == x[i] - 1) {
                printf("NO\n");
                return;
            }
            i = j + 1;
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
