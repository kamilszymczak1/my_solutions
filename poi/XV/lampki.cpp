#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

constexpr long long Pow(long long x, long long exp) {
    long long result = 1;
    while(exp--)
        result *= x;
    return result;
}

struct Number {
    static const int b = 9;
    static const long long base = Pow(10, b);
    char c[b];
    vector<long long>d;
    Number() { d = {}; }
    Number(long long x) {
        do {
            d.push_back(x % base);
            x /= base;
        } while(x != 0);
    }
    void Print() {
        printf("%lld", d.back());
        for(int i = (int)d.size() - 2; i >= 0; i--) {
            long long t = d[i];
            for(int j = b - 1; j >= 0; j--) {
                long long d = t / 10;
                c[j] = t - d * 10;
                t = d;
            }
            for(int j = 0; j < b; j++)
                putchar(c[j] + '0');
        }
    }
};

Number operator/(Number a, long long x) {
    Number result;
    long long r = 0;
    for(int i = (int)a.d.size() - 1; i >= 0; i--) {
        r = r * a.base + a.d[i];
        result.d.push_back(r / x);
        r -= result.d.back() * x;
    }
    reverse(result.d.begin(), result.d.end());
    while(result.d.size() > 1 && result.d.back() == 0)
        result.d.pop_back();
    return result;
}

Number operator*(Number a, long long x) {
    Number result;
    long long r = 0;
    for(int i = 0; i < (int)a.d.size() || r != 0; i++) {
        if(i < a.d.size())
            r += a.d[i] * x;
        long long t = r / a.base;
        result.d.push_back(r - t * a.base);
        r = t;
    }
    while(result.d.size() > 1 && result.d.back() == 0)
        result.d.pop_back();
    return result;
}

long long GCD(long long x, Number a) {
    long long t = 0;
    for(int i = (int)a.d.size() - 1; i >= 0; i--)
        t = (t * a.base + a.d[i]) % x;
    return __gcd(t, x);
}

int main() {
    int n; scanf("%d", &n);
    vector<Number>a(n), b(n);
    vector<int>p(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &p[i]);
    a[n - 1] = Number(1);
    b[n - 1] = Number(p[n - 1]);
    for(int i = n - 2; i >= 0; i--) {
        int g = __gcd(p[i + 1] - 1, p[i]);
        int x = (p[i + 1] - 1) / g, y = p[i] / g;
        if(x == 0) {
            a[i] = Number(0);
            b[i] = Number(1);
        } else {
            int g1 = GCD(x, b[i + 1]);
            int g2 = GCD(y, a[i + 1]);
            a[i] = (a[i + 1] / g2) * (x / g1);
            b[i] = (b[i + 1] / g1) * (y / g2);
        }
    }
    
    for(int i = 0; i < n; i++) {
        a[i].Print();
        putchar('/');
        b[i].Print();
        putchar('\n');
    }
    
    return 0;
}
