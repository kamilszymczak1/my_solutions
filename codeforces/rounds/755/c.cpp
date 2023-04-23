#include <cstdio>
#include <vector>

using namespace std;

int main() {
    int n; scanf("%d", &n);
    vector<int>cnt(n);
    int result = 0, diff = 0;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x); x--;
        if(x == i) {
            result++;
        } else {
            if(cnt[x] == 0)
                diff++;
            cnt[x]++;
        }
    }
    result += diff / 2;
    printf("%d\n", result);
    return 0;
}
