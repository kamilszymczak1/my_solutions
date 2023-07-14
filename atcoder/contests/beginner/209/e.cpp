#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

string FirstThree(string &s) {
    string result = "";
    for(int i = 0; i < 3; i++)
        result += s[i];
    return result;
}

string LastThree(string &s) {
    string result = "";
    for(int i = s.size() - 3; i < s.size(); i++)
        result += s[i];
    return result;
}

void GenIndex(int x, string current, map<string, int>&indexInGraph, int &currentIndex) {
    if(x == 3) {
        indexInGraph[current] = currentIndex++;
        return;
    }
    for(char c = 'a'; c <= 'z'; c++)
        GenIndex(x + 1, current + c, indexInGraph, currentIndex);
    for(char c = 'A'; c <= 'Z'; c++)
        GenIndex(x + 1, current + c, indexInGraph, currentIndex);
}

int main() {
    ios_base::sync_with_stdio(0);
    const int A = 26 * 26 * 26 * 2 * 2 * 2;
    vector<vector<int>>adj(A);
    vector<int>status(A, 0), inDeg(A, 0), inDegLosing(A, 0);
    vector<bool>visited(A, false);
    map<string, int>indexInGraph;
    int currentIndex = 0;
    GenIndex(0, "", indexInGraph, currentIndex);
    int n; cin >> n;
    vector<string>S(n);
    for(string &s : S) {
        cin >> s;
        int a = indexInGraph[FirstThree(s)], b = indexInGraph[LastThree(s)];
        adj[b].push_back(a);
        visited[a] = visited[b] = true;
        inDeg[a]++;
    }
    
    queue<int>q;
    for(int i = 0; i < A; i++) {
        if(inDeg[i] == 0 && visited[i]) {
            status[i] = -1;
            q.push(i);
        }
    }
    
    for(; !q.empty(); q.pop()) {
        int x = q.front();
        if(status[x] == -1) {
            for(int y : adj[x]) {
                if(status[y] != 1) {
                    status[y] = 1;
                    q.push(y);
                }
            }
        } else {
            for(int y : adj[x]) {
                inDegLosing[y]++;
                if(inDegLosing[y] == inDeg[y]) {
                    status[y] = -1;
                    q.push(y);
                }
            }
        }
    }
    
    for(string s : S) {
        int x = status[indexInGraph[LastThree(s)]];
        if(x == 1) {
            cout << "Aoki\n";
        }
        if(x == 0) {
            cout << "Draw\n";
        }
        if(x == -1) {
            cout << "Takahashi\n";
        }
    }
    
    
    return 0;
}
