#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef unsigned long long ull;

const ull mod = (1ull << 61) - 1;
const ull B1 = 175336543, B2 = 120495647;

ull Mult(ull a, ull b) {
    ull l1 = a & 0xffffffff, h1 = a >> 32, l2 = b & 0xffffffff, h2 = b >> 32;
    ull l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    ull result = (h << 3) + (l & mod) + (l >> 61) + (m >> 29) + (m << 35 >> 3) + 1;
    result = (result & mod) + (result >> 61);
    result = (result & mod) + (result >> 61);
    return result - 1;
}

ull Add(ull a, ull b) {
    ull result = a + b;
    if(result >= mod)
        result -= mod;
    return result;
}

void Update(vector<pair<ull, ull>>&x, vector<int>&M, int v) {
    for(auto [y, _] : x) {
        if(y >= M.size())
            y -= M.size();
        M[y] += v;
    }
}

int Count(vector<pair<ull, ull>>&x, vector<int>&M) {
    int result = 0;
    for(auto [y, _] : x) {
        if(y < M.size()) {
            result -= M[y];
        } else {
            result += M[y - M.size()];
        }
    }
    return result;
}

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>a(m);
    vector<pair<int, vector<pair<ull, ull>>>>H(n);
    vector<pair<ull, ull>>allH;
    for(int i = 0; i < n; i++) {
        for(int &x : a)
            scanf("%d", &x);
        sort(a.begin(), a.end());
        for(int j = 1; j < (1 << m); j++) {
            ull h1 = 0, h2 = 0, p = 0;
            for(int k = 0; k < m; k++) {
                if((j >> k) & 1) {
                    p ^= 1;
                    h1 = Add(Mult(h1, B1), (ull)a[k]);
                    h2 = Add(Mult(h2, B2), (ull)a[k]);
                }
            }
            H[i].second.emplace_back(h1 + (p << 63), h2);
            allH.emplace_back(h1, h2);
        }
        scanf("%d", &H[i].first);
    }
    
    sort(H.begin(), H.end(), [&](auto a, auto b) {return a.first < b.first;});
    sort(allH.begin(), allH.end());
    
    int newSize = unique(allH.begin(), allH.end()) - allH.begin();
    allH.resize(newSize);
    for(int i = 0; i < n; i++) {
        for(auto &[h1, h2] : H[i].second) {
            if(h1 >= (1ull << 63)) {
                h1 -= (1ull << 63);
                h1 = lower_bound(allH.begin(), allH.end(), make_pair(h1, h2)) - allH.begin();
                h1 += allH.size();
            } else {
                h1 = lower_bound(allH.begin(), allH.end(), make_pair(h1, h2)) - allH.begin();
            }
        }
    }
    vector<int>M(allH.size());
    int i = 0, total = 0;
    while(i < n && Count(H[i].second, M) == total) {
        Update(H[i].second, M, 1);
        total++;
        i++;
    }
    if(i == n) {
        printf("-1\n");
        return;
    }
    int j = i;
    while(Count(H[i].second, M) != total) {
        j--;
        Update(H[j].second, M, -1);
        total--;
    }
    int result = H[i].first + H[j].first;
    for(i++; i < n && j >= 0; i++) {
        while(j >= 0 && Count(H[i].second, M) != total) {
            j--;
            Update(H[j].second, M, -1);
            total--;
        }
        if(j >= 0)
            result = min(result, H[i].first + H[j].first);
    }
    printf("%d\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
