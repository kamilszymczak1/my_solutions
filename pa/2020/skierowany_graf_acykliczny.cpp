#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_N = 100;
long long fib[MAX_N], k;
int graph[2][MAX_N];

int main() {
    long long k;
    scanf("%lld", &k);
    printf("%d\n", MAX_N);
    for(int i = 0; i < 2; i++)
        fill(graph[i], graph[i] + MAX_N, -1);
    for(int i = 0; i < MAX_N - 1; i++)
        graph[0][i] = i + 2;
    int lastEdges = 0;
    fib[0] = fib[1] = 1;
    for(int i = 2; fib[i - 1] + fib[i - 2] <= k; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        lastEdges++;
    }
    for(int i = 0; i < lastEdges; i++)
        graph[1][MAX_N - lastEdges + i - 2] = MAX_N - lastEdges + i + 1;
    k -= fib[lastEdges + 1];
            
    int last = 0;
    for(int i = lastEdges + 1; i >= 0; i--) {
        if(k - fib[i] >= 0) {
            k -= fib[i];
            graph[1][last++] = MAX_N - i;
        }
    }
    
    for(int i = 0; i < MAX_N; i++)
        printf("%d %d\n", graph[0][i], graph[1][i]);
    
    return 0;
}
