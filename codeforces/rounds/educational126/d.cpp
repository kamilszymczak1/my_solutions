#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long ceil(long long x, long long y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    vector<long long>b(n + 1);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &b[i]);
    vector<long long>a(n + 1);
    long long answer = 0;
    vector<long long>aSuff(n + 2, 0), bSuff(n + 2, 0);
    for(int i = n - k + 1; i > 0; i--) {
        int j = i + k - 1;
        aSuff[j] += aSuff[j + 1];
        bSuff[j] += bSuff[j + 1];
        
        long long value = aSuff[j] * j + bSuff[j];
        
        if(value < b[j]) {
            long long op = ceil(b[j] - value, k);
            aSuff[j] += op;
            aSuff[i - 1] -= op;
            bSuff[j] += (k - j) * op;
            bSuff[i - 1] -= (k - j) * op;
            answer += op;
        }
    }
    long long answer2 = 0;
    for(int i = k - 1; i > 0; i--) {
        aSuff[i] += aSuff[i + 1];
        bSuff[i] += bSuff[i + 1];
        long long value = aSuff[i] * i + bSuff[i];
        if(value < b[i]) {
            long long op = ceil(b[i] - value, i);
            answer2 = max(answer2, op);
        }
    }
    printf("%lld\n", answer + answer2);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
