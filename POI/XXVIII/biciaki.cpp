//Kamil Szymczak - gang biciakow
//O((z + m) * sqrt(n))
//Pomysl na podzial drzewa zaczerpniety z:
//https://codeforces.com/blog/entry/46843
//https://arxiv.org/ftp/arxiv/papers/1303/1303.5481.pdf

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAX_N = 102000, MAX_M = 150007, SQRT = 350, sq = 350;

struct Edge {
    int a, b, color;
    Edge() {}
    Edge(int _a, int _b, int _color) : a(_a), b(_b), color(_color) {}
};

struct Node {
    int color, parent, pre, post, level, superParent, superID;
    vector<int>adj;
    Node() {
        parent = superID = superParent = -1;
        color = level = 0;
    }
};

int cCount[SQRT][MAX_M], preCCount[MAX_M], diff[SQRT], t = -1, diffCount = 0, preDiff = 0;

int n, m, z;
Edge edge[MAX_N];
Node graph[MAX_N];

vector<int>superNodes;

void ReadData();
bool DFS1(int x);
void DFS2(int x);

void FindSpecialNodes(int x);
void ColorNodes();
void FindSuperParent(int x);

int Query(int x);
void Update(int x, int newC);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    DFS1(0);
    ColorNodes();
    DFS2(0);
    
    int a, b;
    char c;
    for(int i = 0; i < z; i++) {
        cin >> c >> a;
        if(c == 'B') {
            cin >> b;
            Update(edge[a - 1].b, b);
        } else
            cout << Query(a - 1) << "\n";
    }
    
    
    return 0;
}

bool DFS1(int x) {
    bool specialBelow = false;
    bool special = graph[x].level % sq == 0;
    graph[x].pre = ++t;
    for(int y : graph[x].adj)
        if(y != graph[x].parent) {
            graph[y].parent = x;
            graph[y].level = graph[x].level + 1;
            if(DFS1(y))
                specialBelow = true;
        }
        
    if((specialBelow && special) || x == 0) {
        graph[x].superID = superNodes.size();
        superNodes.push_back(x);
    }
    graph[x].post = ++t;
    return special || specialBelow;
}

void DFS2(int x) {
    if(graph[x].superID != -1)
        graph[x].superParent = x;
    preCCount[graph[x].color]++;
    
    if(preCCount[graph[x].color] == 1)
        preDiff++;
    
    if(graph[x].superID != -1) {
        for(int i = 0; i <= m; i++)
            cCount[graph[x].superID][i] = preCCount[i];
        diff[graph[x].superID] = preDiff - 1;
    }
    
    for(int y : graph[x].adj)
        if(y != graph[x].parent) {
            graph[y].superParent = graph[x].superParent;
            DFS2(y);
        }
        
    preCCount[graph[x].color]--;
    if(preCCount[graph[x].color] == 0)
        preDiff--;
}

void ColorNodes() {
    for(int i = 0; i < n - 1; i++) {
        if(graph[edge[i].a].pre > graph[edge[i].b].pre)
            swap(edge[i].a, edge[i].b);
        graph[edge[i].b].color = edge[i].color;
    }
}

int Query(int x) {
    int superParent = graph[x].superParent;
    int superID = graph[superParent].superID;
    int result = diff[superID];
    stack<int>s;
    while(x != superParent) {
        if(cCount[superID][graph[x].color] == 0) {
            result++;
            cCount[superID][graph[x].color] = 1;
            s.push(graph[x].color);
        }
        x = graph[x].parent;
    }
    while(!s.empty()) {
        cCount[superID][s.top()] = 0;
        s.pop();
    }
    return result;
}

void Update(int x, int newC) {
    int prevC = graph[x].color;
    for(int i = 0; i < (int)superNodes.size(); i++) {
        if(graph[x].pre <= graph[superNodes[i]].pre && graph[superNodes[i]].pre <= graph[x].post) {
            cCount[i][prevC]--;
            if(cCount[i][prevC] == 0)
                diff[i]--;
            
            cCount[i][newC]++;
            if(cCount[i][newC] == 1)
                diff[i]++;
        }
    }
    graph[x].color = newC;
}

void ReadData() {
    int a, b, color;
    cin >> n >> m >> z;
    for(int i = 0; i < n - 1; i++) {
        cin >> a >> b >> color;
        edge[i] = Edge(a - 1, b - 1, color);
        graph[a - 1].adj.push_back(b - 1);
        graph[b - 1].adj.push_back(a - 1);
    }
}

/*
6 3 5
1 2 3
1 3 2
3 4 3
5 3 1
6 4 2
Z 5
Z 6
B 2 1
Z 5
Z 6
*/
