#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

const int MAX_N = 101;

bool t[MAX_N][MAX_N][MAX_N];
int n;
char c[MAX_N * 7];

bool check(int x, int y, int z) {
    return t[min(x, y)][max(x, y)][z];
}

vector<int> get_adj(int ind) {
    vector<int>which_layer(n, -1);
    vector<vector<int>>layers;
    
    for(int i = 0; i < n; i++) {
        
        if(i == ind)
            continue;
        
        int my_layer = -1;
        for(int j = 0; j < i; j++) {
            if(j == ind)
                continue;
            
            if(t[i][j][ind])
                my_layer = which_layer[j];
        }
        
        if(my_layer == -1) {
            my_layer = layers.size();
            layers.emplace_back();
        }
        
        layers[my_layer].push_back(i);
    }
    
    int s = layers.size();
    for(int i = 0; i < s; i++) {
        //we want to check if the ith layer consist of nodes adjacent to ind
        
        bool ok_list = true;
        for(int j = 0; j < s; j++) {
            if(i == j)
                continue;
            
            for(int k = 0; k < (int)layers[j].size(); k++) {
                for(int l = k + 1; l < (int)layers[j].size(); l++) {
                    bool ok = false;
                    int x = layers[j][k], y = layers[j][l];
                    for(int m = 0; m < (int)layers[i].size(); m++) {
                        int z = layers[i][m];
                        
                        if(t[x][y][z])
                            ok = true;
                    }
                    
                    if(!ok)
                        ok_list = false;
                }
            }
        }
        
        if(ok_list)
            return layers[i];
    }
    return {};
}

void test_case() {
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < n - i; j++) {
            scanf("%s", c);
            for(int k = 0; k < n; k++) {
                t[i][i + j][k] = c[k] - '0';
                t[i + j][i][k] = c[k] - '0';
            }
        }
    }
    
    vector<vector<int>>adj(n);
    
    for(int i = 0; i < n; i++)
        adj[i] = get_adj(i);
    
    printf("adjacency\n");
    
    for(int i = 0; i < n; i++) {
        printf("%d: ", i);
        for(int x : adj[i]) {
            printf("%d ", x);
        }
        printf("\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
