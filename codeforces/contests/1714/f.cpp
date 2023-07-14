#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n, d01, d12, d02;
    scanf("%d%d%d%d", &n, &d01, &d12, &d02);
    
    if(d01 > d02 + d12 || d12 > d02 + d01 || d02 > d12 + d01) {
        printf("NO\n");
        return;
    }
    
    vector<int>id(n);
    for(int i = 0; i < n; i++)
        id[i] = i;
    
    if(d12 >= d01 && d12 >= d02) {
        int a = d01, b = d12, c = d02;
        id[0] = 1;
        id[1] = 2;
        id[2] = 0;
        d01 = b;
        d12 = c;
        d02 = a;
    } else if(d02 >= d01 && d02 >= d12) {
        int a = d01, b = d12, c = d02;
        id[0] = 0;
        id[1] = 2;
        id[2] = 1;
        d01 = c;
        d12 = b;
        d02 = a;
    }
    
    int free_node = 3;
    
    vector<pair<int, int>>edges;
    
    if((d01 + d02 - d12) % 2 != 0) {
        printf("NO\n");
        return;
    }
    
    int x = (d01 + d02 - d12) / 2;
    int y = d01 - x;
    int z = d02 - x;
    
    int left = 0;
    for(int i = 0; i < x - 1; i++) {
        int next = free_node++;
        edges.emplace_back(next, left);
        left = next;
    }
    int right = 1;
    for(int i = 0; i < y - 1; i++) {
        int next = free_node++;
        edges.emplace_back(next, right);
        right = next;
    }
    
    int top = 2;
    for(int i = 0; i < z; i++) {
        int next = free_node++;
        edges.emplace_back(next, top);
        top = next;
    }
    
    edges.emplace_back(top, left);
    edges.emplace_back(top, right);
    
    while(free_node < n)
        edges.emplace_back(0, free_node++);
    
    if(free_node <= n) {
        printf("YES\n");
        for(auto [a, b] : edges)
            printf("%d %d\n", id[a] + 1, id[b] + 1);
    } else {
        printf("NO\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    
    return 0;
}
