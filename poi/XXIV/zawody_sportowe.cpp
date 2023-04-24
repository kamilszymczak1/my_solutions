#include <iostream>
#include <vector>
#include <stack>

#define MAX_N 1000000
#define mod 1000000007

using namespace std;

int n;
vector<int>graph[MAX_N * 2], sure;
int match[MAX_N * 2];
int parent[MAX_N * 2];
bool visited[MAX_N * 2];
long long freePairs;

void ReadData();
void DFSMatch(int beg);
bool Possible();
void DFS(int x);
long long Pow(long long base, int exponent);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    if(!Possible()) {
        cout << "NIE\n0\n";
        return 0;
    }
    
    for(int x : sure)
        DFSMatch(x);
    
    
    
    if(freePairs == 0) {
        cout << "TAK\n";
        for(int i = 0; i < n; i++)
            cout << match[i] + 1 - n << "\n";
    } else {
        cout << "NIE\n";
        int exponent = 0;
        for(int i = 0; i < n; i++)
            if(!visited[i])
                DFS(i), exponent++;
        cout << Pow(2, exponent) << "\n";
    }
    
    return 0;
}

long long Pow(long long base, int exponent) {
    if(exponent == 1)
        return base;
    long long result = Pow(base, exponent / 2);
    result = (result * result) % mod;
    if(exponent % 2 != 0)
        result = (result * base) % mod;
    return result;
}

bool Possible() {
    for(int i = n; i < n * 2; i++)
        if(graph[i].empty())
            return false;
    return true;
}


void DFS(int x) {
    visited[x] = true;
    for(int y : graph[x])
        if(!visited[y])
            DFS(y);
}

void DFSMatch(int beg) {
    int x;
    parent[beg] = -1;
    stack<int>s;
    s.push(beg);
    
    while(!s.empty()) {
        x = s.top();
        s.pop();
        visited[x] = true;
        for(int y : graph[x])
            if(!visited[y]) {
                s.push(y); 
                parent[y] = x;
            }
    }
    
    while(x != -1) {
        match[x] = parent[x];
        match[parent[x]] = x;
        x = parent[parent[x]];
        freePairs--;
    }
}

void ReadData() {
    char c;
    int val;
    cin >> n;
    freePairs = n;
    fill(match, match + 2 * n, -1);
    for(int i = 0; i < n; i++) {
        cin >> c;
        int type = c == 'T' ? 1 : 2;
        for(int j = 0; j < type; j++) {
            cin >> val;
            graph[i].push_back(n + val - 1);
            graph[n + val - 1].push_back(i);
        }
        if(type == 1)
            sure.push_back(i);
    }
}
