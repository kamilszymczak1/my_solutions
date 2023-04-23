#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int inf = 1 << 30;

long long H(vector<int>&v) {
    return (1ll * v[0] << 34) | (1ll * v[1] << 17) | (1ll * v[2]);
}

vector<int> Get(long long x) {
    return {x >> 34, (x >> 17) & ((1 << 17) - 1), x & ((1 << 17) - 1) };
}



void BFS(vector<int>start, vector<int>bound, vector<int>&ans) {
    queue<long long>q;
    map<long long, int>dist;
    dist[H(start)] = 0;
    for(q.push(H(start)); !q.empty(); q.pop()) {
        vector<int>x = Get(q.front());
        int d = dist[q.front()];
        for(int i = 0; i < 3; i++)
            ans[x[i]] = min(ans[x[i]], d);
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j)
                    continue;
                vector<int>y = x;
                y[i] = max(0, x[i] - (bound[j] - x[j]));
                y[j] = min(bound[j], x[i] + x[j]);
                long long h = H(y);
                if(dist.find(h) == dist.end()) {
                    dist[h] = d + 1;
                    q.push(h);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    vector<int>bound(3);
    for(int &x : bound)
        cin >> x;
    vector<int>start(3);
    for(int &x : start)
        cin >> x;
    vector<int>ans(bound[2] + 1, inf);
    BFS(start, bound, ans);
    
    for(int x : ans)
        cout << (x == inf ? -1 : x) << ' ';
    cout << '\n';
    
    return 0;
}

