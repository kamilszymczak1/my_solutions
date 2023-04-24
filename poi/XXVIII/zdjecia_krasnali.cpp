#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAX_N = 500007;

vector<int>graph[MAX_N];
bool visited[MAX_N];
int h[MAX_N], n, m, deg[MAX_N], indeg[MAX_N];

void DFS(int x) {
    visited[x] = true;
    for(int y : graph[x]) {
        if(!visited[y]) {
            DFS(y);
        }
    }
}

void Solve1() {
    
    if(m == 0) {
        cout << "TAK\n";
        for(int i = 0; i < n; i++)
            cout << i + 1 << ' ';
        cout << '\n';
    }
    
    for(int i = 0; i < 2; i++) {
        fill(visited, visited + n, false);
        visited[i] = true;
        int count = 0;
        for(int y : graph[i]) {
            if(!visited[y]) {
                DFS(y);
                count++;
            }
        }
        if(count > 1 || !visited[i ^ 1]) {
            cout << "NIE\n";
            return;
        }
    }
    fill(visited, visited + n, false);
    
    queue<int>q;
    visited[0] = true;
    visited[1] = true;
    q.push(0);
    h[1] = n - 1;
    int index = 0;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        h[x] = index++;
        for(int y : graph[x]) {
            if(!visited[y]) {
                indeg[y]++;
                if(indeg[y] == deg[y] / 2) {
                    visited[y] = true;
                    q.push(y);
                }
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(deg[i] == 0) {
            h[i] = index++;
        }
    }
    
    bool good = true;
    
    for(int i = 2; i < n; i++) {
        int cnt[2] = {0, 0};
        for(int x : graph[i]) {
            if(h[i] < h[x])
                cnt[0]++;
            else
                cnt[1]++;
        }
        if(cnt[0] != cnt[1])
            good = false;
    }
    
    if(good) {
        cout << "TAK\n";
        for(int i = 0; i < n; i++)
            cout << h[i] + 1 << ' ';
        cout << '\n';
    } else {
        cout << "NIE\n";
    }
}

void Brute1() {
    if(n == 2) {
        cout << "TAK\n1 2\n";
        return;
    }
    h[0] = 1;
    h[1] = n;
    for(int i = 2; i < n; i++)
        h[i] = i;
    bool good;
    do {
        good = true;
        for(int i = 2; i < n; i++) {
            int cnt[2] = {0, 0};
            for(int y : graph[i]) {
                if(h[i] < h[y])
                    cnt[0]++;
                else
                    cnt[1]++;
            }
            if(cnt[0] != cnt[1])
                good = false;
        }
    } while(!good && next_permutation(h + 2, h + n));
    if(good) {
        cout << "TAK\n";
        for(int i = 0; i < n; i++)
            cout << h[i] << ' ';
        cout << '\n';
    } else {
        cout << "NIE\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        deg[a - 1]++;
        deg[b - 1]++;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
    if(n <= 10) {
        Brute1();
    } else {
        Solve1();
    }

    return 0;
}
