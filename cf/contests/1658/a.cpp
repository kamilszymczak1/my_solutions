#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    char s[107];
    int n; scanf("%d", &n);
    scanf("%s", s);
    int result = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            int ones = 0;
            int j = i + 1;
            while(j < n && s[j] == '1') {
                j++;
                ones++;
            }
            if(j != n)
                result += max(0, 2 - ones);
        }
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
