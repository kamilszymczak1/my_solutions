#include <cstdio>

using namespace std;

const int MAX_N = 1'000'007;

char c[MAX_N];

int main() {
    int n, h; scanf("%d%d", &n, &h);
    scanf("%s", c);
    
    int current_h = 0, result = 0;
    for(int i = 0; i < n; i++) {
        current_h += c[i] == '(' ? 1 : -1;
        if(current_h < 0) {
            current_h = 1;
            result++;
        }
        if(current_h > h) {
            current_h = h - 1;
            result++;
        }
    }
    
    result += current_h;
    
    printf("%d\n", result);
    
    return 0;
}
