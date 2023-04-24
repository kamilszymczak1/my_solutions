#include <algorithm>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int MAX_N = 500007, MAX_Q = 2000007;
const int LOG = 18;

struct Tuple {
    int a[2], b;
    Tuple() {}
    Tuple(int _a0, int _a1, int _b){
        a[0] = _a0, a[1] = _a1, b = _b;
    }
};

bool operator== (Tuple a, Tuple b) {
    return a.a[0] == b.a[0] && a.a[1] == b.a[1];
}

int n, q, tag[LOG + 1][MAX_N], quantity[MAX_N], result[MAX_Q];
pair<int, int>qu[MAX_Q];
char text[MAX_N];
Tuple newT[MAX_N], t[MAX_N];
vector<pair<int, int>>factors[MAX_N];
vector<int>where[MAX_N];

void RadixSort(int m) {
    for(int i = 1; i >= 0; i--) {
        int hi = 0;
        for(int j = 0; j < m; j++) {
            hi = max(hi, t[j].a[i]);
            quantity[t[j].a[i]]++;
        }
        for(int j = 1; j <= hi; j++)
            quantity[j] += quantity[j - 1];
        for(int j = m - 1; j >= 0; j--)
            newT[--quantity[t[j].a[i]]] = t[j];
        swap(t, newT);
        for(int j = 0; j <= hi; j++)
            quantity[j] = 0;
    }
}


void KMR() {
    for(int i = 0; i < n; i++)
        tag[0][i] = text[i] - 'a';
    for(int i = 1; i <= LOG; i++) {
        int last = n - (1 << i) + 1;
        for(int j = 0; j < last; j++)
            t[j] = Tuple(tag[i - 1][j], tag[i - 1][j + (1 << (i - 1))], j);
        RadixSort(last);
        int currentTag = 0, k = 0;
        while(k < last) {
            do {
                tag[i][t[k].b] = currentTag;
                k++;
            } while(k < last && t[k] == t[k - 1]);
            currentTag++;
        }
    }
}

bool EqualSubstrings(int a, int b, int len) {
    if(len == 0)
        return true;
    int k = 31 - __builtin_clz(len);
    return tag[k][a] == tag[k][b] && tag[k][a + len - (1 << k)] == tag[k][b + len - (1 << k)];
}

bool IsPeriod(int a, int len, int p) {
    return EqualSubstrings(a, a + p, len - p);
}

void FindFactors() {
    for(int i = 2; i <= n; i++) {
        if(factors[i].empty()) {
            for(int j = i; j <= n; j += i) {
                int k = j, c = 0;
                while(k % i == 0) {
                    k /= i;
                    c++;
                }
                factors[j].push_back(make_pair(i, c));
            }
        }
    }
}

void GenerateDivisors(int index, int divisor, int k) {
    if(index == factors[k].size()) {
        for(int i : where[k]) {;
            if(IsPeriod(qu[i].first, qu[i].second, divisor)) {
                result[i] = min(result[i], divisor);
            }
        }
        return;
    }
    for(int i = 0; i <= factors[k][index].second; i++) {
        GenerateDivisors(index + 1, divisor, k);
        divisor *= factors[k][index].first;
    }
}

void Answer() {
    for(int i = 1; i <= n; i++) {
        if(where[i].empty())
            continue;
        GenerateDivisors(0, 1, i);
    }
}

int main() {
    scanf("%d%s%d", &n, &text, &q);
    KMR();
    for(int i = 0; i < q; i++) {
        scanf("%d%d", &qu[i].first, &qu[i].second);
        qu[i].first--;
        qu[i].second -= qu[i].first;
        where[qu[i].second].push_back(i);
        result[i] = qu[i].second;
    }
    FindFactors();
    Answer();
    for(int i = 0; i < q; i++)
        printf("%d\n", result[i]);
    return 0;
}
