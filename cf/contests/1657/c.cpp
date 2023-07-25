#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 500'001;
char c[MAX_N];

void TestCase() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    int i = 0, moves = 0;
    while(i + 1 < n) {
        if(c[i] == ')' && c[i + 1] == '(') {
            int j = i + 2;
            while(j < n && c[j] != ')')
                j++;
            if(j >= n)
                break;
            moves++;
            i = j + 1;
        } else {
            moves++;
            i += 2;
        }
    }
    printf("%d %d\n", moves, n - i);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
