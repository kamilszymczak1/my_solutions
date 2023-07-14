#include <iostream>
#include <queue>
#include <map>

using namespace std;

const long long MAX_N = 100'0007;

long long h(long long x, long long y, long long z) {
    return x * MAX_N * MAX_N + y * MAX_N + z;
}

int BFS(map<long long, int>&dist, int x, int y, int z, int n) {
    dist[h(x, y, z)] = 0;
    queue<long long>q;
    for(q.push(h(x, y, z)); !q.empty(); q.pop()) {
        long long H = q.front();
        x = H / (MAX_N * MAX_N);
        y = (H / MAX_N) % MAX_N;
        z = H % MAX_N;
        
        if(z == n)
            return dist[H];
        
        if(x > 0) {
            int newX = n - y - z + x + 1;
            int newY = n - y + 1;
            int newZ = n - z + 1;
            long long newH = h(newX, newY, newZ);
            if(dist.find(newH) == dist.end()) {
                dist[newH] = dist[H] + 1;
                q.push(newH);
            }
        }
        
        if(y > x) {
            int newX = n - y - z + x;
            int newY = n - y + 1;
            int newZ = n - z - 1;
            long long newH = h(newX, newY, newZ);
            if(dist.find(newH) == dist.end()) {
                dist[newH] = dist[H] + 1;
                q.push(newH);
            }
        }
    }
    
    return -1;
}

void TestCase() {
    int n; cin >> n;
    string a, b; cin >> a >> b;
    int x = 0, y = 0, z = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == b[i]) {
            z++;
            if(a[i] == '1')
                x++;
        }
        if(a[i] == '1')
            y++;
    }
    map<long long, int>dist;
    cout << BFS(dist, x, y, z, n) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    
    
    return 0;
}
