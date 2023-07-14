#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<int> CyclicShift(vector<int>&v, int x) {
    x %= v.size();
    vector<int>result;
    for(int i = (int)v.size() - x; i < (int)v.size(); i++)
        result.push_back(v[i]);
    for(int i = 0; i < (int)v.size() - x; i++)
        result.push_back(v[i]);
    return result;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>C(n), p(n);
    int one = -1;
    vector<pair<int, int>>c(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &C[i]);
        if(C[i] == 1)
            one = i;
    }
    if(n == 1 || one == -1) {
        if(C[0] == 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
        return;
    }
    if(one != 0)
        C = CyclicShift(C, (n - one) % n);
    for(int i = 0; i < n; i++)
        c[i] = make_pair(C[i], i);
    sort(c.begin(), c.end());
    int last = n;
    for(int i = 0; i < n; i++) {
        int j = i;
        vector<int>positions;
        while(j < n && c[j].first == c[i].first) {
            positions.push_back(c[j].second);
            j++;
        }
        if(i == 0 && j != 1) {
            printf("NO\n");
            return;
        }
        sort(positions.begin(), positions.end(), greater<int>());
        for(int x : positions)
            p[(n - x) % n] = last--;
        i = j - 1;
    }
    
    vector<int>realC(n, 0);
    realC[0] = 1;
    vector<pair<int, int>>s;
    s.emplace_back(n, 1);
    for(int i = n - 1; i > 0; i--) {
        while(s.back().first < p[i])
            s.pop_back();
        realC[(n - i) % n] = s.back().second + 1;
        s.emplace_back(p[i], realC[(n - i) % n]);
    }
    if(realC == C) {
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
