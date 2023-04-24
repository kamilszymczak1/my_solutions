#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

map<pair<int, int>, long long>m;

long long DFS(long long x, long long k, vector<vector<int>>&children, vector<long long>&s) {
    
    auto it = m.find(make_pair(x, k));
    if(it != m.end())
        return it -> second;
    
    if(children[x].empty())
        return k * s[x];
    if(children[x].size() == 1) {
        return k * s[x] + DFS(children[x][0], k, children, s);
    }
    
    int def = k / children[x].size();
    int rem = k % children[x].size();
    
    long long answer = k * s[x];
    vector<long long>change;
    for(int y : children[x]) {
        long long a = DFS(y, def, children, s);
        long long b = DFS(y, def + 1, children, s);
        answer += a;
        change.emplace_back(b - a);
    }
    sort(change.begin(), change.end());
    for(int i = 1; i <= rem; i++)
        answer += change[(int)children[x].size() - i];
    return m[{x, k}] = answer;
}

void test_case() {
    m.clear();
    int n; scanf("%d", &n);
    int k; scanf("%d", &k);
    vector<vector<int>>children(n);
    for(int i = 1; i < n; i++) {
        int x; scanf("%d", &x);
        children[x - 1].push_back(i);
    }
    vector<long long>s(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &s[i]);
    printf("%lld\n", DFS(0, k, children, s));
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

