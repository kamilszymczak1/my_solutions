#include <iostream>

#define size 2000

using namespace std;

int length[4][size][size];
bool visited[size][size];
int type[size][size];
int n, m;

int moves[4][2] = {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}};

void FindLines();

int main() {
    ios_base::sync_with_stdio(0);
    string s;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> s;
        for(int j = 0; j < m; j++)
            type[i][j] = s[j] - 'a';
    } 
    
    FindLines();
    
    for(int k = 0; k < 4; k++) {
        cout << "\n" << k + 1 << ":\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                cout << length[k][i][j] << " ";
            cout << "\n";
        }
    }
}

void FindLines() {

    for(int k = 0; k < 4; k++) {
        for(int i = 0; i < n; i++)
            fill(visited[i], visited[i] + m, false);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(!visited[i][j]) {
                    int x = j;
                    int y = i;
                    
                    while(x >= 0 && y >= 0 && x < m && y < n && type[y][x] == type[i][j]) {
                        visited[y][x] = true;
                        length[k][i][j]++;
                        x += moves[k][0];
                        y += moves[k][1];
                    }
                }
                if(length[k][i][j] == 0)
                        length[k][i][j]++;
            }
        }
    }
}
