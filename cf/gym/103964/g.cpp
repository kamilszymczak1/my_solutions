#include <bits/stdc++.h>
using namespace std;
    
int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    
int grid[9][9], visited[9][9];
const int n = 9;
    
int count_adj(int x, int y) {
    queue<pair<int, int>>q;
    q.push(make_pair(x, y));
    visited[x][y] = true;
    set<pair<int, int>>s;
    while(!q.empty()) {
        int a = q.front().first;
        int b = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++) {
            int A = a + moves[i][0];
            int B = b + moves[i][1];
            
            if(A >= 0 && B >= 0 && A < n && B < n) {
                if(grid[A][B] == 1 && !visited[A][B]) {
                    q.push(make_pair(A, B));
                    visited[A][B] = true;
                }
                
                if(grid[A][B] == 0) {
                    s.insert(make_pair(A, B));
                }
            }
        }
    }
    return s.size();
}
    
string test() {
    const int n = 9;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < n; j++) {
            if(s[j] == '.')
                grid[i][j] = 0;
            if(s[j] == 'o')
                grid[i][j] = 1;
            if(s[j] == 'x')
                grid[i][j] = -1;
            visited[i][j] = false;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!visited[i][j] && grid[i][j] == 1) {
                if(count_adj(i, j) == 1)
                    return "Can kill in one move!!!";
            }
        }
    }
    return "Can not kill in one move!!!";
}
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i=1; i<=t; ++i) {
        auto wynik = test();
        cout<<"Case #"<<i<<": "<<wynik<<'\n';
    }
}
