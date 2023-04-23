#include <algorithm>
#include <cstdio>
#include <cmath>

#define sgn(x) (x > 0) ? 1 : (x == 0 ? 0 : -1)

using namespace std;

const int Left = 1, Right = -1, Collinear = 0;
const int MAX_N = 600;
const int MAX_K = 20000;

struct Point {
    int x, y;
    long double cos;
    Point() : x(0), y(0), cos(0) {}
    Point(int _x, int _y) : x(_x), y(_y), cos(0) {}
};

bool pComp(const Point &a, const Point &b) {return a.cos > b.cos;}
long double dot(Point a, Point b, Point c) {return ((b.x - a.x) * (c.x - a.x) + (c.y - a.y) * (b.y - a.y));}
int direction(Point a, Point b, Point c) {return sgn((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));}
long double getCos(Point a, Point b, Point c) {return dot(a, b, c) / (sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y)) * sqrt((c.x - a.x) * (c.x - a.x) + (c.y - a.y) * (c.y - a.y)));}

int dp[MAX_N][MAX_N], pcount[MAX_N][MAX_N];
Point o[MAX_N], p[MAX_K];
int n, k, m;

void ReadData(), CalcCount(), CalcDp();
bool okTriangle(int a, int b, int c);
long double getCos(Point a, Point b, Point c);

int main() {
    
    ReadData();
    CalcCount();
    CalcDp();
    
    printf("%d\n", dp[1][0]);
    
    return 0;
}

bool okTriangle(int a, int b, int c) {
    if(pcount[a][b] == -1 || pcount[b][c] == -1 || pcount[c][a] == -1)
        return false;
    return ((pcount[a][b] + pcount[b][c] + pcount[c][a]) % 2 == 0);
}

void CalcDp() {
    for(int i = 0; i < n; i++)
        dp[i][(i + 1) % n] = 1;
    
    for(int l1 = 2; l1 < n; l1++)
        for(int i = 0; i < n; i++)
            for(int l2 = 1; l2 < l1; l2++)
                if(okTriangle(i, (i + l2) % n, (i + l1) % n))
                    dp[i][(i + l1) % n] = (dp[i][(i + l2) % n] * dp[(i + l2) % n][(i + l1) % n] + dp[i][(i + l1) % n]) % m;
}

void ReadData() {
    scanf("%d%d%d", &n, &k, &m);
    for(int i = 0, x, y; i < n; i++)
        scanf("%d%d", &o[i].x, &o[i].y);
    for(int i = 0, x, y; i < k; i++)
        scanf("%d%d", &p[i].x, &p[i].y);
}

void CalcCount() {
    for(int i = 0; i < n; i++) {
        
        for(int j = 0; j < k; j++)
            p[j].cos = getCos(o[i], o[(i + 1) % n], p[j]);
        
        sort(p, p + k, pComp);
        
        for(int offset = 1, pindex = 0; offset < n; offset++) {
            while(pindex < k && (direction(o[i], o[(i + offset) % n], p[pindex]) == Left))
                pindex++;
            pcount[i][(i + offset) % n] = direction(o[i], o[(i + offset) % n], p[pindex % k]) == Collinear ? -1 : pindex;
        }
    }
}
