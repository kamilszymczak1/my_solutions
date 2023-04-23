#include <iostream>

#define L(x, n) x == 0 ? n - 1 : x - 1
#define R(x, n) x == n - 1 ? 0 : x + 1

#define MAX_N 200000

using namespace std;

bool visited[MAX_N];
bool root[MAX_N];
int branchSize[MAX_N];

int Optimize(int x);

int RDFS(int x);
int LDFS(int x);

int n;
string s;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t;
    cin >> t;
    for(int k = 0; k < t; k++) {
        cin >> n >> s;
        bool rootExists = false;
        fill(root, root + n, false);
        fill(visited, visited + n, false);
        for(int i = 0; i < n; i++)
            if(s[i] == 'R' && s[R(i, n)] == 'L')
                root[i] = true, root[R(i, n)] = true, rootExists = true;
            
        if(!rootExists) {
            cout << Optimize(n) << "\n";
            continue;
        }
        
        int firstL = -1;
        int firstR = -1;
        
        for(int i = 0; i < n; i++) {
            if(firstL == -1 && s[i] == 'L')
                firstL = i;
            if(firstR == -1 && s[i] == 'R')
                firstR = i;
        }
            
        int result = 0;
        
        int pos = firstL;
            
        for(int i = 0; i < n; i++) {
            if(!root[pos] && s[pos] == 'R' && !visited[pos]) {
                int size = RDFS(pos);
                result += Optimize(size - 1);
            }
            pos = R(pos, n);
        }
        
        pos = firstR;
       
        for(int i = 0; i < n; i++) {
            if(!root[pos] && s[pos] == 'L' && !visited[pos]) {
                int size = LDFS(pos);
                result += Optimize(size - 1);
            }
            pos = L(pos, n);
        }
            
        cout << result << "\n";
    }
    
    return 0;
}

int Optimize(int x) {
    if(x % 3 == 0)
        return x / 3;
    return (x / 3) + 1;
}

int RDFS(int x) {
    visited[x] = true;
    int r = R(x, n);
    if(visited[r] || root[r])
        return 1;
    return RDFS(r) + 1;
}

int LDFS(int x) {
    visited[x] = true;
    int l = L(x, n);
    if(visited[l] || root[l])
        return 1;
    return LDFS(l) + 1;
}
