#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Req {
    int a, b, type;
    Req(int _a, int _b, int _type) : a(_a), b(_b), type(_type) {}
};

bool Colour(int x, vector<vector<int>>&adj, vector<int>&colour) {
    for(int y : adj[x]) {
        if(colour[y] == -1) {
            colour[y] = 1 - colour[x];
            if(!Colour(y, adj, colour))
                return false;
        } else if(colour[y] == colour[x]) {
            return false;
        }
    }
    return true;
}

bool TopoDFS(int x, vector<vector<int>>&adj, vector<int>&visited, vector<int>&order) {
    visited[x] = 1;
    for(int y : adj[x]) {
        if(visited[y] == 1)
            return false;
        if(visited[y] == -1) {
            if(!TopoDFS(y, adj, visited, order)) {
                return false;
            }
        }
    }
    order.push_back(x);
    visited[x] = 0;
    return true;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<vector<int>>adj(n);
    vector<Req>req;
    for(int i = 0; i < m; i++) {
        int t, x, y; cin >> t >> x >> y;
        req.emplace_back(x - 1, y - 1, t);
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    vector<int>colour(n, -1);
    for(int i = 0; i < n; i++) {
        if(colour[i] == -1) {
            colour[i] = 0;
            if(!Colour(i, adj, colour)) {
                cout << "NO\n";
                return;
            }
        }
    }
    vector<vector<int>>adj2(n);
    for(Req r : req) {
        int a = r.a, b = r.b;
        if(r.type == 1) {
            if(colour[a] == 0) {
                adj2[a].push_back(b);
            } else {
                adj2[b].push_back(a);
            }
        } else {
            if(colour[a] == 0) {
                adj2[b].push_back(a);
            } else {
                adj2[a].push_back(b);
            }
        }
    }
    vector<int>visited(n, -1), order;
    for(int i = 0; i < n; i++) {
        if(visited[i] == -1) {
            if(TopoDFS(i, adj2, visited, order) == false) {
                cout << "NO\n";
                return;
            }
        }
    }
    vector<char>dir(n);
    vector<int>xco(n);
    cout << "YES\n";
    for(int i = 0; i < n; i++) {
        dir[order[i]] = colour[order[i]] == 0 ? 'L' : 'R';
        xco[order[i]] = -i;
    }
    for(int i = 0; i < n; i++)
        cout << dir[i] << ' ' << xco[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
