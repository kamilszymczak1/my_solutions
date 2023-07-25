#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Mine {
    int x, y, id;
    Mine(int _x, int _y, int _id) : x(_x), y(_y), id(_id) {}
};

bool cmp1(Mine &a, Mine &b) {
    if(a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool cmp2(Mine &a, Mine &b) {
    if(a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

int DFS(int x, vector<bool>&visited, vector<vector<int>>&adj, vector<int>&timer) {
    int result = timer[x];
    visited[x] = true;
    for(int y : adj[x]) {
        if(!visited[y]) {
            result = min(result, DFS(y, visited, adj, timer));
        }
    }
    return result;
}

void TestCase() {
    vector<Mine>mines;
    int n, k; cin >> n >> k;
    vector<int>timer(n);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y >> timer[i];
        mines.emplace_back(x, y, i);
    }
    vector<vector<int>>adj(n);
    sort(mines.begin(), mines.end(), cmp1);
    for(int i = 0; i < n - 1; i++) {
        if(mines[i].x == mines[i + 1].x) {
            if(abs(mines[i].y - mines[i + 1].y) <= k) {
                adj[mines[i].id].push_back(mines[i + 1].id);
                adj[mines[i + 1].id].push_back(mines[i].id);
            }
        }
    }
    sort(mines.begin(), mines.end(), cmp2);
    for(int i = 0; i < n - 1; i++) {
        if(mines[i].y == mines[i + 1].y) {
            if(abs(mines[i].x - mines[i + 1].x) <= k) {
                adj[mines[i].id].push_back(mines[i + 1].id);
                adj[mines[i + 1].id].push_back(mines[i].id);
            }
        }
    }
    
    vector<int>startTime;
    vector<bool>visited(n, false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            startTime.push_back(DFS(i, visited, adj, timer));
        }
    }
    sort(startTime.begin(), startTime.end());
    int index = 0;
    for(int i = 0; i < n; i++) {
        while(index < startTime.size() && startTime[index] <= i)
            index++;
        if(startTime.size() - index <= i + 1) {
            cout << i << '\n';
            return;
        }
    }
    cout << n << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
