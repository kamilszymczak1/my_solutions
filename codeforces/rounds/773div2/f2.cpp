#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

const int MAX_N = 100;

struct DynamicSet {
    struct Node {
        int value;
        map<int, int>to;
        Node() : value(0) {}
    } nodes[MAX_N * 80];
    int t;
    vector<int>*x;
    int NewNode() {
        t++;
        return t - 1;
    }
    DynamicSet() {
        t = 1;
    }
    void AddRec(int v, int i, int val) {
        if(i == x -> size()) {
            nodes[v].value += val;
            return;
        }
        if(nodes[v].to.find((*x)[i]) == nodes[v].to.end())
            nodes[v].to[(*x)[i]] = NewNode();
        AddRec(nodes[v].to[(*x)[i]], i + 1, val);
        AddRec(v, i + 1, val);
    }
    void Add(vector<int>&X, int val) {
        x = &X;
        AddRec(0, 0, val);
    }
    int CountRec(int v, int i, int depth) {
        if(i == x -> size()) {
            return nodes[v].value * (2 * depth - 1);
        }
        int result = 0;
        if(nodes[v].to.find((*x)[i]) != nodes[v].to.end())
            result += CountRec(nodes[v].to[(*x)[i]], i + 1, 1 - depth);
        return result + CountRec(v, i + 1, depth);
    }
    int Count(vector<int>&X) {
        x = &X;
        return CountRec(0, 0, 0);
    }
};

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<pair<int, vector<int>>>v(n, make_pair(0, vector<int>(m, 0)));
    for(int i = 0; i < n; i++) {
        for(int &x : v[i].second)
            scanf("%d", &x);
        scanf("%d", &v[i].first);
        sort(v[i].second.begin(), v[i].second.end());
    }
    sort(v.begin(), v.end());
    DynamicSet S;
    int i = 0, total = 0;
    while(i < n && S.Count(v[i].second) == total) {
        S.Add(v[i].second, 1);
        i++;
        total++;
    }
    if(i == n) {
        printf("-1\n");
        return 0;
    }
    int j = i;
    while(S.Count(v[i].second) != total) {
        j--;
        S.Add(v[j].second, -1);
        total--;
    }
    int result = v[i].first + v[j].first;
    for(i++; i < n && j >= 0; i++) {
        while(j >= 0 && S.Count(v[i].second) != total) {
            j--;
            S.Add(v[j].second, -1);
            total--;
        }
        if(j >= 0)
            result = min(result, v[i].first + v[j].first);
    }
    printf("%d\n", result);
    return 0;
}
