#include <iostream>

#define MAX_N 25

using namespace std;

long long arr[MAX_N][MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    
    int n = 25;
    
    for(int i = 0; i < n; i++)
        arr[0][i] = 1, arr[i][0] = 1;
    
    for(int i = 1; i < n; i++)
        for(int j = 1; j < n; j++)
            arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
        
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << arr[i][j] << " ";
        cout << "\n";
    }
    
    return 0;
}
