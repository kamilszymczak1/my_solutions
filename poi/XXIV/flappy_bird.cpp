#include <iostream>
#include <cmath>

#define MAX_N 500002

using namespace std;

int n, X;

int x[MAX_N];
int maxH[MAX_N];
int minH[MAX_N];

int Solve();

void Load();

int main() {
    ios_base::sync_with_stdio(0);
    
    Load();
    
    int result = Solve();
    
    if(result == -1)
        cout << "NIE\n";
    else
        cout << result << "\n";
    
    return 0;
}

int Solve() {
    
    for(int i = 0; i <= n; i++)
        if(minH[i] >= maxH[i])
            return -1;
    
    int posY = 0;
    int posX = 0;
    
    int result = 0;
    
    for(int i = 1; i <= n; i++) {
        
        int dx = x[i] - x[i - 1];
        int minY = minH[i] + 1;
        int maxY = maxH[i] - 1;
        
        int minPossibleY = posY - dx;
        
        if(minY >= minPossibleY) {
            result += (minY - minPossibleY) / 2;
            posY = minY;
        }
        if(minY < minPossibleY) {
            posY = minPossibleY;
        }
    }
    
    return result;
}

void Load() {
    
    cin >> n >> X;
    
    x[0] = 0;
    minH[0] = -1;
    maxH[0] = 1;
    
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> minH[i] >> maxH[i];
        if(x[i] % 2 == 0) {
            if(abs(minH[i]) % 2 == 0)
                minH[i]++;
            if(abs(maxH[i]) % 2 == 0)
                maxH[i]--;
        } else {
            if(abs(minH[i]) % 2 == 1)
                minH[i]++;
            if(abs(maxH[i]) % 2 == 1)
                maxH[i]--;
        }
    }
    
    for(int i = n - 1; i >= 0; i--) {
        int dx = x[i + 1] - x[i];
        minH[i] = max(minH[i], minH[i + 1] - dx);
        maxH[i] = min(maxH[i], maxH[i + 1] + dx);
    }
}
