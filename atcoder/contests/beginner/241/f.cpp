#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

map<pair<int, int>, int>d;
pair<int, int>start, finish;
int n, h, w;

int main() {
    ios_base::sync_with_stdio(0);
    cin >> h >> w >> n;
    cin >> start.first >> start.second;
    cin >> finish.first >> finish.second;
    map<int, vector<int>>horizontal, vertical;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        horizontal[y].push_back(x);
        vertical[x].push_back(y);
    }
    for(auto &[y,vec] : horizontal)
        sort(vec.begin(), vec.end());
    for(auto &[x, vec] : vertical)
        sort(vec.begin(), vec.end());
    
    d[start] = 1;
    queue<pair<int, int>>q;
    q.push(start);
    while(!q.empty()) {
        int x = q.front().first, y = q.front().second;
        int D = d[make_pair(x, y)];
        //left, right
        vector<int>&H = horizontal[y];
        if(!H.empty()) {
            int ind = lower_bound(H.begin(), H.end(), x) - H.begin();
            if(ind != H.size()) {
                int newX = H[ind] - 1;
                if(d[make_pair(newX, y)] == 0) {
                    d[make_pair(newX, y)] = D + 1;
                    q.push(make_pair(newX, y));
                }
            }
            if(ind != 0) {
                int newX = H[ind - 1] + 1;
                if(d[make_pair(newX, y)] == 0) {
                    d[make_pair(newX, y)] = D + 1;
                    q.push(make_pair(newX, y));
                }
            }
        }
        
        vector<int>&V = vertical[x];
        if(!V.empty()) {
            int ind = lower_bound(V.begin(), V.end(), y) - V.begin();
            if(ind != V.size()) {
                int newY = V[ind] - 1;
                if(d[make_pair(x, newY)] == 0) {
                    d[make_pair(x, newY)] = D + 1;
                    q.push(make_pair(x, newY));
                }
            }
            if(ind != 0) {
                int newY = V[ind - 1] + 1;
                if(d[make_pair(x, newY)] == 0) {
                    d[make_pair(x, newY)] = D + 1;
                    q.push(make_pair(x, newY));
                }
            }
        }
        
        q.pop();
    }
    
    cout << d[finish] - 1 << '\n';
    
    return 0;
}
