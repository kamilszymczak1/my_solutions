#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int main() {
    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    
    vector<pair<long long, int>>v;
    for(int i = 0; i < n + m; i++) {
        int x; scanf("%d", &x);
        v.emplace_back(x, i < n);
    }
    sort(v.begin(), v.end());
    vector<int>l(n + m), r(n + m), f(n + m);
    for(int i = 0; i < n + m; i++)
        l[i] = r[i] = f[i] = i;
    
    auto find = [&f](int x, auto &&find) -> int {
        return f[x] == x ? f[x] : f[x] = find(f[x], find);
    };
    
    vector<pair<int, int>>queries;
    for(int i = 0; i < q; i++) {
        int k; scanf("%d", &k);
        queries.emplace_back(k, i);
    }
    sort(queries.begin(), queries.end());
    
    vector<long long>answers(q);
    
    vector<pair<int, int>>merges;
    for(int i = 0; i < n + m - 1; i++) {
        merges.emplace_back(v[i + 1].first - v[i].first, i);
    }
    sort(merges.begin(), merges.end());
    
    long long answer = 0;
    for(auto [value, count] : v)
        answer += value * count;
    
    for(int i = 1; i < n + m; i++)
        v[i].first += v[i - 1].first;
    
    auto get_value = [&v, &f, &l, &r, &find] (int x) -> long long {
        x = find(x, find);
        int count = v[x].second;
        long long result = v[r[x]].first;
        if(r[x] - count >= 0)
            result -= v[r[x] - count].first;
        return result;
    };
    
    int j = 0;
    for(auto [len, index] : queries) {
        while(j < n + m - 1 && merges[j].first <= len) {
            
            int a = find(merges[j].second, find);
            int b = find(merges[j].second + 1, find);
            
            answer -= get_value(a);
            answer -= get_value(b);
            
            r[a] = r[b];
            f[b] = a;
            v[a].second += v[b].second;
            v[b].second = 0;
            
            answer += get_value(a);
            
            j++;
        }
        
        answers[index] = answer;
    }
    
    for(long long x : answers)
        printf("%lld\n", x);
    
    return 0;
}

