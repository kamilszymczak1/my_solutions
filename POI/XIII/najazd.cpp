#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

const int MAX_N = 600;
const int MAX_M = 10000;

struct Point {
    int x, y, income;
    long double cos;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    inline bool operator() (Point &a, Point &b) {return a.cos > b.cos;}
};

inline Point operator- (Point a, Point b) {return Point(a.x - b.x, a.y - b.y);}
long double getCos(Point a, Point b) {return (a.x * b.x + a.y * b.y) / (sqrt(a.x * a.x + a.y * a.y) * sqrt(b.x * b.x + b.y * b.y));}
bool left(Point a, Point b) {return (a.x * b.y - a.y * b.x > 0);}
void ReadData(), CalcIncome();

bool badPoint[MAX_M];
Point o[MAX_N], p[MAX_M];
int income[MAX_N][MAX_N], pointIncome[MAX_N], n, m, incomeSum = 0;

int main() {
    
    ReadData();
    CalcIncome();
    
    int result = 0;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            for(int k = j + 1; k < n; k++)
                result = max(result, incomeSum - income[i][j] - income[j][k] - income[k][i] + pointIncome[i] + pointIncome[j] + pointIncome[k]);
    
    printf("%d\n", result);
            
    return 0;
}

void CalcIncome() {
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(o[i].x == p[j].x && o[i].y == p[j].y)
                badPoint[j] = true, pointIncome[i] += p[j].income, incomeSum -= p[j].income;

    int m1 = m, m = 0;
    for(int i = 0; i < m1; i++)
        if(!badPoint[i])
            p[m++] = p[i];
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            p[j].cos = getCos(o[(i + 1) % n] - o[i], p[j] - o[i]);
        
        sort(p, p + m, Point());
        for(int offset = 2, currentSum = 0, pindex = 0; offset < n; offset++) {
            while(pindex < m && left(o[(i + offset) % n] - o[i], p[pindex] - o[i]))
                currentSum += p[(pindex++) % m].income;
            income[i][(i + offset) % n] = currentSum;
        }
    }
}

void ReadData() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &o[i].x, &o[i].y);
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].income);
        incomeSum = incomeSum + p[i].income;
    }
}
