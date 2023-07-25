#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

string sub2(string &s, int x) {
    return s.substr(x, 2);
}
string sub3(string &s, int x) {
    return s.substr(x, 3);
}

void TestCase() {
    struct Info {
        int a, b, id;
        Info(int _a, int _b, int _id) : a(_a), b(_b), id(_id) {}
        Info() {
            a = b = id = -1;
        }
    };
    map<string, Info>twos, threes;
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m - 1; j++)
            twos[sub2(s, j)] = Info(j + 1, j + 2, i + 1);
        for(int j = 0; j < m - 2; j++)
            threes[sub3(s, j)] = Info(j + 1, j + 3, i + 1);
    }
    string s; cin >> s;
    vector<Info>parent(m);
    if(m == 1) {
        cout << "-1\n";
        return;
    }
    if(twos.find(sub2(s, 0)) != twos.end())
        parent[1] = twos[sub2(s, 0)];
    if(m > 2 && threes.find(sub3(s, 0)) != threes.end())
        parent[2] = threes[sub3(s, 0)];
    for(int i = 3; i < m; i++) {
        if(twos.find(sub2(s, i - 1)) != twos.end() && parent[i - 2].a != -1)
            parent[i] = twos[sub2(s, i - 1)];
        if(threes.find(sub3(s, i - 2)) != threes.end() && parent[i - 3].a != -1)
            parent[i] = threes[sub3(s, i - 2)];
    }
    if(parent[m - 1].a == -1) {
        cout << "-1\n";
        return;
    }
    vector<Info>path;
    for(int i = m - 1; i > 0; i -= parent[i].b - parent[i].a + 1)
        path.push_back(parent[i]);
    cout << path.size() << '\n';
    for(int i = (int)path.size() - 1; i >= 0; i--)
        cout << path[i].a << ' ' << path[i].b << ' ' << path[i].id << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
