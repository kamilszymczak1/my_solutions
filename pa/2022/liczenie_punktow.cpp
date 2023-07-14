#include <cstdio>

using namespace std;

const int MAX_N = 107;
char c[MAX_N];

int main() {
    int n; scanf("%d", &n);
    scanf("%s", c);
    int answer = 0;
    for(int i = 0; i < 10; i++) {
        int cnt = 0;
        for(int j = (n / 10) * i; j < (n / 10) * (i + 1); j++) {
            cnt += c[j] == 'T';
        }
        if(cnt == n / 10)
            answer++;
    }
    printf("%d\n", answer);
    return 0;
}
