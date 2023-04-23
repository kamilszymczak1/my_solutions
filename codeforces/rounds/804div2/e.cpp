#include <cstdio>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cassert>

using namespace std;

//const int MAX_M = 5'000'000;
const int MAX_M = 200;

pair<int, int> primes[30];
int divisors[10'000], primes_head = 0, divisors_head = 0, bound, sieve[MAX_M + 1];
vector<long long>intervals[MAX_M + 1];

void gen_divisors(int pos, int d) {
    if(pos == primes_head) {
        divisors[divisors_head++] = d;
        return;
    }
    for(int i = 0; i <= primes[pos].second && 1ll * d * d <= bound; i++) {
        gen_divisors(pos + 1, d);
        d *= primes[pos].first;
    }
}

int first(long long x) { return x >> 32; }
int second(long long x) { return x & ((1ll << 32) - 1); }
long long bound_pair(long long a, long long b) { return b | (a << 32); }

void preprocessing() {
    fill(sieve, sieve + MAX_M, -1);
    for(long long i = 2; i <= MAX_M; i++) {
        if(sieve[i] == -1) {
            sieve[i] = i;
            for(long long j = i * i; j <= MAX_M; j += i) {
                sieve[j] = i;
            }
        }
    }
    
    int sum = 0;
    for(int i = 1; i <= MAX_M; i++) {
        primes_head = 0;
        int total_count = 0;
        for(int x = i; x != 1; ) {
            int count = 0, d = sieve[x];
            while(x % d == 0) {
                count++;
                x /= d;
            }
            total_count += count;
            primes[primes_head++] = make_pair(d, count);
        }
        bound = i;
        divisors_head = 0;
        gen_divisors(0, 1);
        sort(divisors, divisors + divisors_head, greater<int>());
        intervals[i].reserve(total_count);
        intervals[i].emplace_back(bound_pair(i, i));
        for(int j = 0; j < divisors_head - 1; j++) {
            int d = divisors[j];
            int k = i / d;
            auto it = lower_bound(intervals[k].begin(), intervals[k].end(), bound_pair(d, 0));
            if(it != intervals[k].end() && second(*it) < second(intervals[i].back()))
                intervals[i].emplace_back(bound_pair(d, second(*it)));
        }
        reverse(intervals[i].begin(), intervals[i].end());
        intervals[i].shrink_to_fit();
        printf("%d: ", i);
        for(long long x : intervals[i])
            printf("(%d, %d) ", first(x), second(x));
        printf("\n");
    }
}

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    
    vector<int>mx(m + 3, 0);
    int min_a = 1 << 30;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        min_a = min(min_a, x);
        mx[1] = max(mx[1], second(intervals[x][0]));
        for(int j = 1; j < (int)intervals[x].size(); j++) {
            int k = first(intervals[x][j - 1]);
            mx[k + 1] = max(mx[k + 1], second(intervals[x][j]));
        }
    }
    int hi = 0, result = 1 << 30;
    for(int lo = 1; lo <= min_a; lo++) {
        hi = max(hi, mx[lo]);
        result = min(result, hi - lo);
    }
    printf("%d\n", result);
}

int main() {
    preprocessing();
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
