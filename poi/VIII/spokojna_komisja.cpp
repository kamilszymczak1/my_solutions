#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 8000 * 4;

vector<int>graph[MAX_N];
vector<int>graphT[MAX_N];
bool visited[MAX_N];
int status[MAX_N];
int n, m;

int sccNumber[MAX_N];
vector<vector<int>>scc;
vector<int>order;



void ReadData();

bool satiable();
void topoDFS1(int x);
void topoDFS2(int x);
void findSatisfiability();
void statusDFS(int x);
int getNegation(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    if(satiable()) {
        
        findSatisfiability();
        
        for(int i = 0; i < n; i += 2)
            cout << i + 2 - status[i] << "\n";
        
    } else
        cout << "NIE\n";
    
    return 0;
}

void findSatisfiability() {
    
    fill(status, status + n * 2, -1);
    
    for(vector<int>&v : scc) {
        if(status[v[0]] != -1)
            continue;
        
        for(int x : v)
            statusDFS(getNegation(x));
    }
    
}

void statusDFS(int x) {
    status[x] = 1;
    status[getNegation(x)] = 0;
    for(int y : graph[x])
        if(status[y] == -1)
            statusDFS(y);
}

bool satiable() {
    
    for(int i = 0; i < n; i++)
        if(!visited[i])
            topoDFS1(i);
    
    for(int i = n * 2 - 1; i; i--)
        if(sccNumber[order[i]] == 0) {
            scc.push_back(vector<int>());
            topoDFS2(order[i]);
        }
    
    for(int i = 0; i < n; i++)
        if(sccNumber[i] == sccNumber[i + n])
            return false;
        
    return true;
}

void topoDFS1(int x) {
    visited[x] = true;
    for(int y : graph[x])
        if(!visited[y])
            topoDFS1(y);
    order.push_back(x);
}

void topoDFS2(int x) {
    scc.back().push_back(x);
    sccNumber[x] = scc.size();
    for(int y : graphT[x])
        if(sccNumber[y] == 0)
            topoDFS2(y);
}

void ReadData() {
    int a, b;
    cin >> n >> m;
    n = n * 2;
    for(int i = 0; i < n; i += 2) {
        graph[i + 0].push_back(i + n + 1);
        graph[i + 1].push_back(i + n + 0);
        graph[i + n + 1].push_back(i + 0);
        graph[i + n + 0].push_back(i + 1);
        
        graphT[i + 0].push_back(i + n + 1);
        graphT[i + 1].push_back(i + n + 0);
        graphT[i + n + 1].push_back(i + 0);
        graphT[i + n + 0].push_back(i + 1);
    }
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        a--, b--;
        graph[a].push_back(b + n);
        graph[b].push_back(a + n);
        
        graphT[a + n].push_back(b);
        graphT[b + n].push_back(a);
    }
}

int getNegation(int x) {
    if(x < n)
        return x + n;
    return x - n;
}
