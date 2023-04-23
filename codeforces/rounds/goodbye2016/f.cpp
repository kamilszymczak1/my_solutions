#include <cstdio>

using namespace std;

vector<int> query(int x) {
    printf("? %d\n", x + 1);
    fflush(stdout);
    int k; scanf("%d", &k);
    vector<int>ret(k);
    for(int &x : ret) {
        scanf("%d", &x);
        x--;
    }
    return ret;
}

void test_case() {
    running = true;
    int h; scanf("%d", &h);
    vector<vector<int>>adj((1 << h) - 1);
    
    vector<int>path(1, 0), visited(n, false);
    adj[0] = query(0);
    visited[0] = true;
    if(adj[0].size() == 2) {
        printf("! 1\n");
        fflush(stdout);
        return;
    }
    
    if(adj[0].size() == 1) {
        //0 is a leaf
        //we advance to the top
    } else {
        //0 is not a leaf
        
    }
    
    
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
