#include <iostream>
#include <vector>

using namespace std;

const int leafCount = 1 << 18;
int tree[leafCount * 2];

const int MAX_N = 250000;
int n, m, t = -1;
int pre[MAX_N];
int post[MAX_N];
int dist[MAX_N];
vector<int>graph[MAX_N];
bool visited[MAX_N];

void DFS(int x);
void ReadData();
void Add(int a, int b, int val);
int Query(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    DFS(0);
    
    char c;
    int a;
    cin >> m;
    for(int i = 1; i < n + m; i++) {
        cin >> c >> a;
        if(c == 'W')
            cout << dist[a - 1] - Query(pre[a - 1]) << "\n";
        else {
            cin >> a;
            Add(pre[a - 1], post[a - 1], 1);
        }
    }
    
    return 0;
}

void DFS(int x) {
    visited[x] = true;
    pre[x] = ++t;
    for(int y : graph[x])
        if(!visited[y])
            dist[y] = dist[x] + 1, DFS(y);
    post[x] = t;
}

void ReadData() {
    int a, b;
    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
}

int Query(int x) {
    x += leafCount;
    int result = 0;
    while(x) {
        result += tree[x];
        x >>= 1;
    }
    return result;
}

void Add(int a, int b, int val) {
    a += leafCount;
    b += leafCount;
    tree[a] += val;
    if(a != b)
        tree[b] += val;
    while(a / 2 != b / 2) {
        if(a % 2 == 0)
            tree[a + 1] += val;
        if(b % 2 == 1)
            tree[b - 1] += val;
        a >>= 1;
        b >>= 1;
    }
}
