#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool Prime(long long y) {
    for(long long x = 2; x * x <= y; x++) {
        if(y % x == 0) {
            return false;
        }
    }
    return true;
}

long long Gen(long long current, int ind, long long k, long long d, vector<long long>&div) {
    if(k == 0)
        return current == 1;
    int result = 0;
    for(int i = ind; i < div.size(); i++) {
        if(current % div[i] == 0) {
            result += Gen(current / div[i], i, k - 1, d, div);
        }
        if(result >= 2)
            break;
    }
    return result;
}

int Cnt(long long t, long long k, long long d) {
    if(t % d == 0) {
        if(Prime(d))
            return 0;
        vector<long long>div;
        for(long long i = 1; i * i <= t; i++) {
            if(t % i == 0) {
                if(i % d != 0)
                    div.push_back(i);
                if((t / i) % d != 0)
                    div.push_back(t / i);
            }
        }
        return Gen(t, 0, k, d, div);
    } else {
        return Prime(t) ? 1 : 2;
    }
}

void TestCase() {
    long long x, d; scanf("%lld%lld", &x, &d);
    if(x % (d * d) != 0) {
        printf("NO\n");
        return;
    }
    long long dz = d;
    int ways = 0, k = 1;
    while(dz <= x) {
        if(x % dz == 0) {
            long long t = x / dz;
            ways += Cnt(t, k, d);
//             printf("dz = %lld\n", dz);
//             printf("cnt = %d\n", Cnt(t, k, d));
        }
        dz *= d;
        k++;
    }
    if(ways > 1) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
