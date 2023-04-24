#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 5000
#define MAX_K 1000000
#define inf (1 << 30)

using namespace std;

struct Query {
    int to, d;
    bool result;
    Query() {
        result = false;
    }
    Query(int a, int dist) {
        to = a;
        d = dist;
        result = false;
    }
};

Query querries[MAX_K];
vector<int>nodeQuery[MAX_N];
vector<int>graph[MAX_N * 2];
int dist[MAX_N * 2];
int n, m, k;

void ReadData();
void BFS(int beg);
void SolveQuerries();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    SolveQuerries();
    
    for(int i = 0; i < k; i++)
        if(querries[i].result)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    
    return 0;
}

void SolveQuerries() {
    for(int i = 0; i < n; i++) {
        if(nodeQuery[i].empty() || graph[i].empty())
            continue;
        
        BFS(i);
        
        for(int qpointer : nodeQuery[i]) {
            Query q = querries[qpointer];
            int fullDist = (q.d % 2 == 0 ? dist[q.to] : dist[q.to + n]);
            
            if(fullDist <= q.d)
                querries[qpointer].result = true;
            else
                querries[qpointer].result = false;
            
        }
    }
}

void BFS(int beg) {
    for(int i = 0; i < n + n; i++)
        dist[i] = inf;
    dist[beg] = 0;
    queue<int>q;
    q.push(beg);
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        
        for(int y : graph[x])
            if(dist[y] == inf) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
    }
}

void ReadData() {
    int a, b, c;
    cin >> n >> m >> k;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1 + n);
        graph[b - 1].push_back(a - 1 + n);
        graph[a - 1 + n].push_back(b - 1);
        graph[b - 1 + n].push_back(a - 1);
    }
    
    for(int i = 0; i < k; i++) {
        cin >> a >> b >> c;
        nodeQuery[a - 1].push_back(i);
        querries[i] = Query(b - 1, c);
    }
}
