#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_N 50000
#define MAX_V 100000

#define size MAX_N * 2

using namespace std;

struct Position {
    int row, index;
    Position() {
        row = -1;
        index = -1;
    }
};

Position positions[MAX_V];
vector<int>graph[size];
bool visited[size];

vector<vector<int>>components;

int n;

void ReadData();
int GetNegation(int x);
int DFS(int x);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int result = 0;
    
    for(int i = 0; i < n; i++)
        if(!visited[i])
            result += min(DFS(i), DFS(i + n));
        
    cout << result << "\n";
    
    return 0;
}

int DFS(int x) {
    visited[x] = true;
    int result = (x >= n);
    for(int y : graph[x])
        if(!visited[y])
            result += DFS(y);
    return result;
}

void ReadData() {
    cin >> n;
    for(int i = 0; i < 2; i++) {
        int h;
        for(int j = 0; j < n; j++) {
            cin >> h;
            
            if(positions[h - 1].row != -1) {
                int a = j, b = positions[h - 1].index;
                int notA = GetNegation(a), notB = GetNegation(b);
                if(positions[h - 1].row == i) {
                    graph[a].push_back(notB);
                    graph[notB].push_back(a);
                    graph[b].push_back(notA);
                    graph[notA].push_back(b);
                } else {
                    graph[a].push_back(b);
                    graph[b].push_back(a);
                    graph[notA].push_back(notB);
                    graph[notB].push_back(notA);
                }
            } else {
                positions[h - 1].row = i;
                positions[h - 1].index = j;
            }
        }
    }
    
}

int GetNegation(int x) {
    if(x >= n)
        return x - n;
    return x + n;
}
