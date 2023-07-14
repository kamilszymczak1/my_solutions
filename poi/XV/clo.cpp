#include <iostream>
#include <vector>
#include <queue>

#define MAX_N 100000
#define MAX_M 200000
#define size MAX_N + MAX_M

using namespace std;

vector<int>graph[size];
bool visited[size];
int match[size];
int parent[size];
int n, m;

void ReadData();
bool Possible();
bool CheckDFS(int n, int p);
void FindMatching();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    if(Possible()) {
        
        FindMatching();
        
        cout << "TAK\n";
        for(int i = 0; i < n; i++)
            cout << (graph[match[i]][0] == i ? graph[match[i]][1] : graph[match[i]][0]) + 1 << "\n";
    } else
        cout << "NIE\n";
    
    return 0;
}

void FindMatching() {
    fill(match, match + n + m, -1);
    
    bool found;
    
    do {
        found = false;
        fill(visited, visited + n + m, false);
        
        for(int i = 0; i < n; i++) {
            if(match[i] > 0 || visited[i])
                continue;

            queue<int>q;
            visited[i] = true;
            parent[i] = -1;
            q.push(i);
            
            while(!q.empty()) {
                int x = q.front();
                q.pop();
                
                if(x >= n) {
                    if(match[x] == -1) {
                        while(x != -1) {
                            if(x >= n) {
                                match[x] = parent[x];
                                match[parent[x]] = x;
                            }
                            x = parent[x];
                        }
                        found = true;
                        break;
                    } else {
                        parent[match[x]] = x;
                        visited[match[x]] = true;
                        q.push(match[x]);
                    }
                } else {
                    for(int y : graph[x]) {
                        if(!visited[y]) {
                            visited[y] = true;
                            parent[y] = x;
                            q.push(y);
                        }
                    }
                }
            }
        }  
    } while(found);
}

bool Possible() {
    for(int i = 0; i < n; i++)
        if(!visited[i] && !CheckDFS(i, -1))
            return false;
    return true;
}

bool CheckDFS(int n, int p) {
    bool result = false;
    visited[n] = true;
    for(int x : graph[n]) {
        if(!visited[x]) {
            if(CheckDFS(x, n))
                result = true;
        } else if(x != p)
            result = true;
    }
    return result;
}

void ReadData() {
    int a, b;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(n + i);
        graph[n + i].push_back(a - 1);
        graph[b - 1].push_back(n + i);
        graph[n + i].push_back(b - 1);
    }
}
