#include <cstdio>
#include <vector>

using namespace std;

#define LSB(x) (x & (-x))

struct FenwickTree {
    vector<int>values;
    FenwickTree(int n) {
        values.resize(n + 1);
    }
    void AddOne(int x) {
        for(x++; x < (int)values.size(); x += LSB(x))
            values[x]++;
    }
    int PrefixSum(int x) {
        int result = 0;
        for(x++; x; x -= LSB(x))
            result += values[x];
        return result;
    }
};

char NextChar() {
    char ans;
    do ans = getchar(); while(ans != '+' && ans != '-');
    return ans;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<FenwickTree>T(3, FenwickTree(2 * n / 3 + 1));
    long long result = 0;
    T[n % 3].AddOne(n / 3);
    for(int i = n; i > 0; i--) {
        n += NextChar() == '+' ? -1 : 1;
        result += T[n % 3].PrefixSum(n / 3);
        T[n % 3].AddOne(n / 3);
    }
    printf("%lld\n", result);
}
int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
