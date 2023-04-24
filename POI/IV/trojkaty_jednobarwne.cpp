#include <iostream>

#define MAX_N 1000

using namespace std;

int count[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m, a, b;
    cin >> n >> m;
    
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        count[a - 1]++;
        count[b - 1]++;
    }
    
    int allTriangles = n * (n - 1) * (n - 2) / 6;
    
    int result = 0;
    
    for(int i = 0; i < n; i++)
        result += count[i] * (n - count[i] - 1);
    
    result = allTriangles - (result >> 1);
    
    cout << result << "\n";
    
    return 0;
}

/*
6
9
1
2
2
1
1
3
4
5
3
2
3
5
4
6
4
5
6
6
*/
