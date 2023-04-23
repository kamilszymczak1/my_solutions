#include <iostream>

using namespace std;

const long long inf = 1000000000000000000;

struct NewCost {
    long long cost;
    int pos;
    NewCost() {}
    NewCost(long long _cost, int _pos) : cost(_cost), pos(_pos) {}
};


NewCost best[3][3];
long long totalCost = 0;

void ReadData();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    long long result = inf;
    
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                if(best[0][i].pos != best[1][j].pos && best[0][i].pos != best[2][k].pos && best[1][j].pos != best[2][k].pos)
                    result = min(result, best[0][i].cost + best[1][j].cost + best[2][k].cost);
                
    cout << result + totalCost << "\n";
    
    return 0;
}

void ReadData() {
    long long a[3], n;
    NewCost x[3];
    bool allZero[3] = {true, true, true};
    
    for(int i = 0; i < 3; i++)
        fill(best[i], best[i] + 3, NewCost(inf, 0));
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[0] >> a[1] >> a[2];
        
        for(int j = 0; j < 3; j++)
            allZero[j] = (a[j] != 0) ? false : allZero[j];
        
        long long shelfCost = min(a[0] + a[1], min(a[1] + a[2], a[0] + a[2]));
        x[0] = NewCost(a[1] + a[2] - shelfCost, i);
        x[1] = NewCost(a[0] + a[2] - shelfCost, i);
        x[2] = NewCost(a[0] + a[1] - shelfCost, i);
        
        totalCost += shelfCost;
        
        for(int j = 0; j < 3; j++) {
            if(x[j].cost <= best[j][0].cost) {
                best[j][2] = best[j][1];
                best[j][1] = best[j][0];
                best[j][0] = NewCost(x[j].cost, i);
            } else if(x[j].cost <= best[j][1].cost) {
                best[j][2] = best[j][1];
                best[j][1] = NewCost(x[j].cost, i);
            } else if(x[j].cost < best[j][2].cost)
                best[j][2] = NewCost(x[j].cost, i);
        }
    }
    for(int i = 0; i < 3; i++)
        if(allZero[i])
            fill(best[i], best[i] + 3, NewCost(0, -1 * (i + 1)));
}
