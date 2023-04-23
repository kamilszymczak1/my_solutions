#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int K = 300;

void TestCase() {
    int n, q;
    cin >> n >> q;
    vector<int>small(n), big(n), prev(n);
    for(int i = 0; i < n; i++) {
        cin >> small[i];
        small[i]--;
    }
    for(int i = 0; i < n; i++)
        prev[small[i]] = i;
    for(int i = 0; i < n; i++) {
        big[i] = i;
        for(int k = 0; k < K; k++)
            big[i] = small[big[i]];
    }
    
    for(int Q = 0; Q < q; Q++){
        int t; cin >> t;
        if(t == 1) {
            int x, y; cin >> x >> y; x--; y--;
            int prevX = prev[x], prevY = prev[y];
            swap(small[x], small[y]);
            big[x] = x; big[y] = y;
            for(int k = 0; k < K; k++) {
                big[x] = small[big[x]];
                big[y] = small[big[y]];
            }
            prev[small[x]] = x;
            prev[small[y]] = y;
            for(int k = 0; k < K; k++) {
                x = prev[x];
                y = prev[y];
                big[x] = prev[big[small[x]]];
                big[y] = prev[big[small[y]]];
            }
        } else {
            int i, k; cin >> i >> k;
            i--;
            while(k > 0) {
                if(k >= K) {
                    i = big[i];
                    k -= K;
                } else {
                    i = small[i];
                    k--;
                }
            }
            cout << i + 1 << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    
    return 0;
}
