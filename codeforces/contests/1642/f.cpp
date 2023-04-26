#include <algorithm>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

const int MAX_N = 100'000;

struct DynamicSet {
    struct Node {
        int value;
        map<int, int>to;
        Node() : value(0) {}
    };
    vector<Node>nodes;
    int t;
    int NewNode() {
        nodes.emplace_back();
        return nodes.size() - 1;
    }
    DynamicSet() {
        nodes.resize(1, Node());
    }
    void AddRec(int v, int i, vector<int>&x, int val) {
        nodes[v].value += val;
        for(int j = i; j < x.size(); j++) {
            if(nodes[v].to.find(x[j]) == nodes[v].to.end())
                nodes[v].to[x[j]] = NewNode();
            AddRec(nodes[v].to[x[j]], j + 1, x, val);
        }
    }
    void Add(vector<int>&x, int val) {
        AddRec(0, 0, x, val);
    }
    int CountRec(int v, int i, vector<int>&x, int depth) {
        int result = nodes[v].value * (depth * 2 - 1);
        if(v == 0)
            result = 0;
        for(int j = i; j < x.size(); j++) {
            if(nodes[v].to.find(x[j]) != nodes[v].to.end()) {
                result += CountRec(nodes[v].to[x[j]], j + 1, x, 1 - depth);
            }
        }
        return result;
    }
    int Count(vector<int>&x) {
        return CountRec(0, 0, x, 0);
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
    sort(v.begin(), v.end(), [&](const auto &a, const auto &b) {return a.first < b.first;});
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
