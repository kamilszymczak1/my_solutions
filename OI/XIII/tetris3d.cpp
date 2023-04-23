#include <cstdio>

using namespace std;

int max(int a, int b) {return a > b ? a : b;}
int min(int a, int b) {return a < b ? a : b;}

int _time = 0;
struct Node {
    int w, W, wx, wy, lastVisit; 
    //wx - max among all children with the same (x1, x2)
    //wy - max among all children with the same (y1, y2)
    Node() : w(0), W(0), wx(0), wy(0), lastVisit(0) {}
} nodes[1 << 11][1 << 11];

int GetMax(int ax, int bx, int ay, int by, int lox, int hix, int loy, int hiy, int vx, int vy) { 
    if(nodes[vx][vy].lastVisit == _time || ax >= bx || ay >= by) {
        return 0;
    }
    nodes[vx][vy].lastVisit = _time;
    if(ax == lox && bx == hix && ay == loy && by == hiy) {
        return nodes[vx][vy].w;
    }   
    const int midx = (lox + hix) >> 1, midy = (loy + hiy) >> 1;
    int result = nodes[vx][vy].W;
    if(ax != lox || bx != hix) {
        result = max(result, GetMax(ax, min(bx, midx), ay, by, lox, midx, loy, hiy, vx * 2, vy));
        result = max(result, GetMax(max(ax, midx), bx, ay, by, midx, hix, loy, hiy, vx * 2 + 1, vy));
    } else {
        result = max(result, nodes[vx][vy].wy);
    }
    if(ay != loy || by != hiy) {
        result = max(result, GetMax(ax, bx, ay, min(midy, by), lox, hix, loy, midy, vx, vy * 2));
        result = max(result, GetMax(ax, bx, max(midy, ay), by, lox, hix, midy, hiy, vx, vy * 2 + 1));
    } else {
        result = max(result, nodes[vx][vy].wx);
    }
    return result;
}

void SetMax(int ax, int bx, int ay, int by, int lox, int hix, int loy, int hiy, int value, int vx, int vy) {
    if(nodes[vx][vy].lastVisit == _time || ax >= bx || ay >= by) {
        return;
    }
    nodes[vx][vy].lastVisit = _time;
    if(ax == lox && bx == hix && ay == loy && by == hiy) { 
        nodes[vx][vy].W = max(nodes[vx][vy].W, value);
        nodes[vx][vy].w = max(nodes[vx][vy].w, value);
        nodes[vx][vy].wx = max(nodes[vx][vy].wx, value);
        nodes[vx][vy].wy = max(nodes[vx][vy].wy, value);
        return;
    }
        
    const int midx = (lox + hix) >> 1, midy = (loy + hiy) >> 1;
    
    if(ax != lox || bx != hix) {
        SetMax(ax, min(bx, midx), ay, by, lox, midx, loy, hiy, value, vx * 2, vy);
        SetMax(max(ax, midx), bx, ay, by, midx, hix, loy, hiy, value, vx * 2 + 1, vy);
    }
    
    if(ay != loy || by != hiy) {
        SetMax(ax, bx, ay, min(by, midy), lox, hix, loy, midy, value, vx, vy * 2);
        SetMax(ax, bx, max(ay, midy), by, lox, hix, midy, hiy, value, vx, vy * 2 + 1);
    }
    
    nodes[vx][vy].w = max(nodes[vx][vy].w, nodes[vx][vy].W);
    if(hix - lox > 1) {
        nodes[vx][vy].w = max(nodes[vx][vy].w, max(nodes[vx * 2][vy].w, nodes[vx * 2 + 1][vy].w));
        nodes[vx][vy].wy = max(max(nodes[vx][vy].W, nodes[vx][vy].wy), max(nodes[vx * 2][vy].wy, nodes[vx * 2 + 1][vy].wy));
    }
    if(hiy - loy > 1) {
        nodes[vx][vy].w = max(nodes[vx][vy].w, max(nodes[vx][vy * 2].w, nodes[vx][vy * 2 + 1].w));
        nodes[vx][vy].wx = max(max(nodes[vx][vy].wx, nodes[vx][vy].W), max(nodes[vx][vy * 2].wx, nodes[vx][vy * 2 + 1].wx));
    }
}

int main() {
    int D, S, N, gridSize, d, s, w, x, y;
    scanf("%d%d%d", &D, &S, &N);
    for(gridSize = 1; gridSize < max(D, S); gridSize <<= 1) {}
    
    while(N--) {
        scanf("%d%d%d%d%d", &d, &s, &w, &x, &y);
        _time++;
        int M = GetMax(x, x + d, y, y + s, 0, gridSize, 0, gridSize, 1, 1);
        _time++;
        SetMax(x, x + d, y, y + s, 0, gridSize, 0, gridSize, M + w, 1, 1);
    }
    
    printf("%d\n", nodes[1][1].w);
    
    return 0;
}

/*
 7 5 4
 4 3 2 0 0
 3 3 1 3 0
 7 1 2 0 3
 2 3 3 2 2
*/
