#include <iostream>

#define MAX_N 200

using namespace std;

bool possible[MAX_N][MAX_N];
int a[MAX_N];
int b[MAX_N];
int n, m;
bool ommited[9];

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < m; i++)
        cin >> b[i];
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            possible[i][j] = true;
        
    for(int i = 0; i < 9; i++)
        ommited[i] = true;
    
    for(int i = 8; i >= 0; i--) {
        for(int j = 0; j < n; j++) {
            bool ommitedLocal = false;
            for(int k = 0; k < m; k++) {
                int x = a[j] & b[k];
                x = x & (1 << i);
                if(possible[j][k] && x == 0)
                    ommitedLocal = true;
            }
            if(!ommitedLocal)
                ommited[i] = false;
        }
        if(ommited[i]) {
            ommited[i] = true;
            for(int j = 0; j < n; j++) {
                for(int k = 0; k < m; k++) {
                    int x = a[j] & b[k];
                    x = x & (1 << i);
                    if(x != 0)
                        possible[j][k] = false;
                }
            }
        }
    }
    
    int result = 0;
    for(int i = 0; i < 9; i++)
        if(!ommited[i])
            result += 1 << i;
        
    cout << result << "\n";
    
    return 0;
}
