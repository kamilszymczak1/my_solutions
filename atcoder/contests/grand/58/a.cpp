#include <cstdio>
#include <algorithm>
#include <vector>
    
using namespace std;


int main() {
    
    int n; scanf("%d", &n);
    vector<int>a(2 * n);
    vector<int>moves;
    for(int &x : a)
        scanf("%d", &x);
    
    for(int i = 1; i + 2 < 2 * n; i += 2) {
        int x = a[i], y = a[i + 1], z = a[i + 2];
        
        if(x < y && y < z) {
            //<, < -> >, <
            swap(a[i], a[i + 1]);
            moves.push_back(i);
        }
        
        if(x > y && y > z) {
            //>, > -> >, <
            swap(a[i + 1], a[i + 2]);
            moves.push_back(i + 1);
        }
        
        if(x < y && y > z) {
            //<, > -> >, <
            if(x < z) {
                swap(a[i], a[i + 1]);
                moves.push_back(i);
            } else {
                swap(a[i + 1], a[i + 2]);
                moves.push_back(i + 1);
            }
        }
        
    }
    
    if(a[0] > a[1]) {
        swap(a[0], a[1]);
        moves.push_back(0);
    }
    
    printf("%d\n", (int)moves.size());
    for(int x : moves)
        printf("%d ", x + 1);
    printf("\n");
    
    return 0;
}
