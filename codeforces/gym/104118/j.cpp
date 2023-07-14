#include <iostream>
#include <vector>
    
using namespace std;
    
const int MAX_N = 107;
char grid[MAX_N][MAX_N];
    
int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector<pair<int, int>>points;
    for(int i = 0; i < n; i++) {
        string t; cin >> t;
        for(int j = 0; j < m; j++) {
            if(t[j] == '#') {
                points.emplace_back(i, j);
            }
            grid[i][j] = '.';
        }
    }
    
    for(int i = points[0].first; i <= points[1].first; i++)
        grid[i][points[0].second] = '#';
    if(points[0].second < points[1].second) {
        for(int i = points[0].second; i <= points[1].second; i++)
            grid[points[1].first][i] = '#';
    } else {
        for(int i = points[1].second; i <= points[0].second; i++)
            grid[points[1].first][i] = '#';
    }
    
    if(points[1].second < points[2].second) {
        for(int i = points[1].second; i <= points[2].second; i++)
            grid[points[1].first][i] = '#';
    } else {
        for(int i = points[2].second; i <= points[1].second; i++)
            grid[points[1].first][i] = '#';
    }
    
    
    for(int i = points[1].first; i <= points[2].first; i++) {
        grid[i][points[2].second] = '#';
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
    
    
    return 0;
}
