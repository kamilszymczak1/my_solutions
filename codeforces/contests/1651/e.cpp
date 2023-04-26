#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void DFS(int x, vector<vector<int>>&adj, vector<bool>&visited, vector<int>&cycle) {
    cycle.push_back(x);
    visited[x] = true;
    for(int y : adj[x]) {
        if(!visited[y]) {
            DFS(y, adj, visited, cycle);
        }
    }
}

long long Calc(vector<int>&l, vector<int>&r, vector<int>x, int n) {
    vector<int>choiceL = {l[0] + 1, l[1] + 1 - n};
    vector<int>choiceR = {n - r[0], 2 * n - r[1]};
    for(int y : x) {
        int a = y / n;
        if(l[a] <= y && y <= r[a])
            return 0;
        if(y < l[a]) {
            choiceL[a] = min(choiceL[a], l[a] - y);
        } else {
            choiceR[a] = min(choiceR[a], y - r[a]);
        }
    }
    long long result = 1ll * choiceL[0] * choiceL[1];
    result = result * choiceR[0] * choiceR[1];
    return result;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<vector<int>>adj(2 * n);
    for(int i = 0; i < n * 2; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    vector<bool>visited(2 * n, false);
    long long result = 0;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            vector<int>cycle;
            DFS(i, adj, visited, cycle);
            int s = cycle.size();
            vector<int>l = {n, 2 * n};
            vector<int>r = {0, n};
            for(int x : cycle) {
                int a = x / n;
                l[a] = min(l[a], x);
                r[a] = max(r[a], x);
            }
            result += Calc(l, r, {}, n) * (s / 2);
            for(int k = 0; k < s; k++) {
                l = {n, 2 * n};
                r = {0, n};
                for(int j = 0; j < s - 1; j++) {
                    int a = cycle[j] / n;
                    l[a] = min(l[a], cycle[j]);
                    r[a] = max(r[a], cycle[j]);
                    result += Calc(l, r, {cycle[s - 1], cycle[j + 1]}, n) * ((j + 1) / 2);
                }
                for(int j = 0; j < s - 1; j++)
                    swap(cycle[j], cycle[j + 1]);
            }
        }
    }
    printf("%lld\n", result);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
