#include <cstdio>
#include <vector>
    
using namespace std;
    
void DFS(int x, int p, vector<vector<pair<int, long long>>>&adj, vector<long long>&prefix_xor, vector<long long>&A) {
    for(auto [y, w] : adj[x]) {
        if(prefix_xor[y] == -1) {
            prefix_xor[y] = prefix_xor[x] ^ w;
            DFS(y, x, adj, prefix_xor, A);
        } else if(y != p) {
            A.push_back(prefix_xor[y] ^ prefix_xor[x] ^ w);
        }
    }
}
    
bool ith_bit(long long x, int i) {
    return (x >> i) & 1;
}
    
long long test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<pair<int, long long>>>adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; scanf("%d%d", &a, &b); a--; b--;
        long long c; scanf("%lld", &c);
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
    }
    
    vector<long long>prefix_xor(n, -1), A;
    prefix_xor[0] = 0;
    DFS(0, -1, adj, prefix_xor, A);
    
    const int B = 60;
    vector<long long>M(B, 0);
    for(long long x : A) {
        for(int i = B - 1; i >= 0; i--) {
            if(ith_bit(M[i], i)) {
                if(ith_bit(x, i)) {
                    x ^= M[i];
                }
            } else {
                if(ith_bit(x, i)) {
                    M[i] = x;
                    break;
                }
            }
        }
    }
    
    long long answer = 0;
    for(int i = B - 1; i >= 0; i--) {
        if(!ith_bit(answer, i) && ith_bit(M[i], i))
            answer ^= M[i];
    }
    
    return answer;
}
    
int main() {
    int t; scanf("%d", &t);
    for(int i = 1; i <= t; i++) {
        printf("Case #%d: %lld\n", i, test_case());
    }
    return 0;
}
