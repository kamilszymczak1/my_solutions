#include <cstdio>
#include <algorithm>

using namespace std;

const int SORT_BITS = 15;
constexpr unsigned long long bit30 = (1ull << 30) - 1;
constexpr unsigned long long bits = (1ull << SORT_BITS) - 1;
unsigned long long n, a, b, currentTime, result;
unsigned long long p[200000], p1[200000];
int lastIndex[1 << SORT_BITS];

void swap(unsigned long long *&a, unsigned long long *&b) {
    unsigned long long *c = a;
    a = b; b = c;
}

void RadixSort() {
    for(int i = 0; i < 2; i++) {
        const int shift = i * SORT_BITS;
        for(int j = 0; j < n; j++)
            lastIndex[(p[j] >> shift) & bits]++;
        for(int j = 1; j <= bits; j++)
            lastIndex[j] += lastIndex[j - 1];
        for(int j = n - 1; j >= 0; j--)
            p1[--lastIndex[(p[j] >> shift) & bits]] = p[j];
        swap(p, p1);
        if(!i) {
            for(int j = 0; j <= bits; j++)
                lastIndex[j] = 0;
        }
    }
}

int main() {
    scanf("%lld", &n);
    for(int i = 0; i < n; i++) {
        scanf("%lld%lld", &a, &b);
        p[i] = (a << 30) | b;
    }
    RadixSort();
    for(int i = 0; i < n; i++) {
        if((p[i] >> 30) >= currentTime) {
            currentTime = p[i] & bit30;
            result++;
        }
    }
    printf("%lld\n", result);
    return 0;
}
