#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int reverse(int x) {
    int last = x % 10;
    int pow10 = 1;
    while(pow10 <= x / 10)
        pow10 *= 10;
    return x / 10 + last * pow10;
}

int main() {
    ios_base::sync_with_stdio(0);
    int a, n; cin >> a >> n;
    int pow10 = 1;
    while(pow10 <= n)
        pow10 *= 10;
    vector<int>dist(pow10, -1);
    dist[1] = 0;
    queue<int>q;
    for(q.push(1); !q.empty(); q.pop()) {
        int x = q.front();
        if(1ll * x * a < 1ll * pow10 && dist[x * a] == -1) {
            dist[x * a] = dist[x] + 1;
            q.push(x * a);
        }
        if(x >= 10 && x % 10 != 0) {
            int y = reverse(x);
            if(dist[y] == -1) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }
    
    cout << dist[n] << '\n';
    
    return 0;
}
