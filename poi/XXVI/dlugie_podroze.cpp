#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

const int MAX_N = 100007, T = 100;

vector<int>adj[MAX_N];
int d[T][MAX_N], n, m, p;
bool visited[MAX_N], used[MAX_N];

int randint(int bound) {
    int result = 0;
    for(int i = 0; i < 3; i++)
        result = (result << 8) | (rand() & 0xff);
    return result % bound;
}

void BFS(int index, int source) {
    fill(visited, visited + n, false);
    queue<int>q;
    d[index][source] = 0;
    visited[source] = true;
    for(q.push(source); !q.empty(); q.pop()) {
        int x = q.front();
        for(int y : adj[x]) {
            if(!visited[y]) {
                visited[y] = true;
                d[index][y] = d[index][x] + 1;
                q.push(y);
            }
        }
    }
}

void Prepare() {
    for(int i = 0; i < min(n, T); i++) {
        int x;
        do {
            x = randint(n);
        } while(used[x]);
        BFS(i, x);
        used[x] = true;
    }
}

int Query(int x, int y) {
    int result = MAX_N;
    for(int i = 0; i < min(n, T); i++)
        result = min(result, d[i][x] + d[i][y]);
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    srand(time(NULL));
    cin >> n >> m >> p;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
    
    Prepare();
    
    while(p--) {
        int x, y;
        cin >> x >> y;
        cout << Query(x - 1, y - 1) << '\n';
    }
    
    return 0;
}

/*
6 7 2
1 2
2 4
3 1
3 4
4 5
4 6
6 5
2 5
1 6
*/
