#include <cstdio>
#include <vector>

using namespace std;

void gen_queries(int lo, int hi, vector<vector<vector<int>>>&queries, int depth) {
    if(depth < 0)
        return;
    
    int mid = (lo + hi) / 2;
    for(int i = lo; i < mid; i++)
        queries[depth][0].push_back(i);
    for(int i = mid; i < hi; i++)
        queries[depth][1].push_back(i);
    
    gen_queries(lo, mid, queries, depth - 1);
    gen_queries(mid, hi, queries, depth - 1);
}

void get(vector<int>&answer, vector<int>&columns, int n) {
    while(!columns.empty() && columns.back() >= n)
        columns.pop_back();
    if(columns.empty())
        return;
    printf("%d\n", (int)columns.size());
    vector<bool>unlocked(n, true);
    for(int x : columns) {
        unlocked[x] = false;
        printf("%d ", x + 1);
    }
    printf("\n");
    fflush(stdout);
    vector<int>response(n);
    for(int &x : response)
        scanf("%d", &x);
    
    for(int i = 0; i < n; i++) {
        if(unlocked[i]) {
            answer[i] = min(answer[i], response[i]);
        }
    }
}

int main() {
    int n, h = 0; scanf("%d", &n);
    while((1 << h) < n)
        h++;
    vector<vector<vector<int>>>queries(h, vector<vector<int>>(2));
    gen_queries(0, 1 << h, queries, h - 1);
    
    vector<int>answer(n, 1 << 30);
    
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < 2; j++) {
            get(answer, queries[i][j], n);
        }
    }
    
    printf("-1\n");
    for(int x : answer)
        printf("%d ", x);
    printf("\n");
    fflush(stdout);
    
    return 0;
}
