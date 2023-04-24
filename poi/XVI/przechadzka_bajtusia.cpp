#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 400
#define MAX_D 100
#define R 26

#define tabSize (MAX_N * MAX_N * (R + 1))

using namespace std;

struct Parent {
    int from;
    char mask;
    Parent() {
        from = -1;
        mask = -1;
    }
    Parent(int a, char b) {
        from = a;
        mask = b;
    }
};

struct Edge {
    int to;
    char mask;
    Edge(int a, char b) {
        to = a;
        mask = b;
    }
};

queue<int>q;

vector<Edge>graph[MAX_N], graphp[MAX_N];
int n, m, d;

Parent parent[tabSize];
char finish[tabSize];

int s[MAX_D];

void ReadData();
void BFS();
string FindPath(int beg);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    BFS();
    
    for(int i = 1; i < d; i++) {
        int beg = s[i - 1] * n + s[i];
        string result = FindPath(beg);
        if(result == "")
            cout << "-1\n";
        else
            cout << result.size() << " " << result << "\n";
    }
    
    return 0;
}

string FindPath(int beg) {
    string result = "";
    if(parent[beg].mask == -1)
        return result;
    
    while(parent[beg].from != -2) {
        if(beg / (n * n) > 0)
            result = result + parent[beg].mask;
        beg = parent[beg].from;
    }
    
    int size = result.size();
    
    if(finish[beg] > 1)
        result = result + finish[beg];
    
    for(int i = size - 1; i >= 0; i--)
        result = result + result[i];
    
    return result;
}

void BFS() {
    
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        
        int letter = x / (n * n);
        int a = (x % (n * n)) / n;
        int b = x % n;
        
        if(letter == 0) {
            for(Edge e : graph[a]) {
                int y = (e.mask - 'a' + 1) * n * n + e.to * n + b;
                if(parent[y].mask == -1)
                    parent[y] = Parent(x, e.mask), q.push(y);
            }
        } else {
            for(Edge e : graphp[b]) {
                if(e.mask - 'a' + 1 == letter) {
                    int y = a * n + e.to;
                    if(parent[y].mask == -1)
                        parent[y] = Parent(x, e.mask), q.push(y);
                }
            }
        }
    }
}

void ReadData() {
    int a, b;
    char c;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        finish[i * n + i] = 1;
        parent[i * n + i] = Parent(-2, -2);
        q.push(i * n + i);
    }
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        a--;
        b--;
        graph[b].push_back(Edge(a, c));
        graphp[a].push_back(Edge(b, c));
        finish[a * n + b] = c;
        parent[a * n + b] = Parent(-2, -2);
        q.push(a * n + b);
    }
    cin >> d;
    for(int i = 0; i < d; i++)
        cin >> s[i], s[i]--;
}
