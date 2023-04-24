#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};
const int moves[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
const int MAX_N = 2000, SIZE = 6010, inf = 999999999;
bool obstacle[SIZE][SIZE], available[SIZE][SIZE], outOfBounds[SIZE][SIZE];
short nearestObstacle[SIZE][SIZE];
char inputGrid[MAX_N][MAX_N], v[MAX_N][MAX_N];
int n, gridSize, dpL[SIZE], dpR[SIZE];
int longestPrefL[SIZE], longestPrefR[SIZE], maxR[MAX_N], maxRe = 0, result = inf;
Point initBoatPos(-1, -1), leftmost = Point(SIZE, SIZE), rightmost = Point(-1, -1);
vector<Point>boat;
int bottomOffset = 0, boatSize = 0;
void ReadData(), go(int x, int y, int newD, queue<pair<Point, int>>&q);
bool OutOfBounds(int x, int y), symmetricVertically(vector<Point>v);
int main() {
    ios_base::sync_with_stdio(0);
    ReadData();
    
    
    for(Point p : boat) {
        maxR[p.y - leftmost.y] = max(maxR[p.y - leftmost.y], p.x - leftmost.x + 1);
        maxRe = max(p.y - leftmost.y + 1, maxRe);
    }
    
    for(int i = leftmost.y; i <= 0; i++)
        longestPrefL[maxR[i - leftmost.y]] = max(longestPrefL[maxR[i - leftmost.y]], i - leftmost.y + 1);
    
    for(int i = 1; i < gridSize; i++)
        longestPrefL[i] = max(longestPrefL[i], longestPrefL[i - 1]);
    
    for(int i = 0; i <= rightmost.y; i++)
        longestPrefR[maxR[i - leftmost.y]] = max(longestPrefR[maxR[i - leftmost.y]], rightmost.y - i + 1);
    
    for(int i = 0; i < gridSize; i++)
        longestPrefR[i] = max(longestPrefR[i], longestPrefR[i - 1]);
    
    
    for(int j = 0; j < gridSize; j++) {
        for(int i = 0, last = -boatSize; i < gridSize; i++) {
            if(obstacle[i][j])
                last = i;
            nearestObstacle[i][j] = i - last;
        }
        for(int i = gridSize - 1, last = gridSize + boatSize; i >= 0; i--) {
            if(obstacle[i][j])
                last = i;
            nearestObstacle[i][j] = min((int)nearestObstacle[i][j], last - i);
        }
    }
    
    int leftOffset = abs(leftmost.y) + 1, rightOffset = abs(rightmost.y) + 1;
    for(int i = 0; i < gridSize; i++) {
        dpL[0] = leftOffset;
        for(int j = 1; j < gridSize; j++) {
            dpL[j] = min(longestPrefL[nearestObstacle[i][j]], dpL[j - 1] + 1);
        }
        dpR[gridSize - 1] = rightOffset;
        for(int j = gridSize - 2; j >= 0; j--) {
            dpR[j] = min(longestPrefR[nearestObstacle[i][j]], dpR[j + 1] + 1);
        }
        for(int j = 0; j < gridSize; j++)
            available[i][j] = dpL[j] == leftOffset && dpR[j] == rightOffset;
    }
    
    
    queue<pair<Point, int>>q;
    Point start(leftmost.x + initBoatPos.x, initBoatPos.y);
    available[start.x][start.y] = false;
    q.push(make_pair(start, 0));
    while(!q.empty()) {
        pair<Point, int>p = q.front();
        q.pop();
        if(OutOfBounds(p.first.x, p.first.y)) {
            result = p.second;
            break;
        }
        for(int i = 0; i < 4; i++)
            go(p.first.x + moves[i][0], p.first.y + moves[i][1], p.second + 1, q);
    }
    if(result == inf)
        cout << "NIE\n";
    else
        cout << result << '\n';
    
    return 0;
}

bool OutOfBounds(int x, int y) {
    if(x >= boatSize && x < boatSize + n && y >= boatSize && y < boatSize + n)
        return false;
    int lo = 0, hi = 0;
    if(y < boatSize) {
        int dist = boatSize - (y + leftmost.y);
        if(dist < maxRe) {
            lo = x - maxR[dist] + 1;
            hi = x + maxR[dist] - 1;
        }
    } else if(y >= boatSize + n) {
        int dist = y + rightmost.y - (boatSize + n) + 1;
        if(dist < maxRe) {
            lo = x - maxR[maxRe - dist - 1] + 1;
            hi = x + maxR[maxRe - dist - 1] - 1;
        }
    } else {
        hi = x + (bottomOffset >> 1);
        lo = x - (bottomOffset >> 1);
    }
    if((hi >= boatSize && hi < boatSize + n) || (lo >= boatSize && lo < boatSize + n))
        return false;
    return true;
}

bool symmetricVertically(vector<Point>v) {
    int minL = 0;
    for(Point p : v)
        minL = min(p.y, minL);
    for(Point &p : v) {
        p.y -= minL;
        available[p.x][p.y] = true;
    }   
    int symmetryAxe = (-minL) * 2;
    for(Point p : v)
        if(!available[p.x][symmetryAxe - p.y])
            return false;
    for(Point p : v)
        available[p.x][p.y] = false;
    return true;
}

void go(int x, int y, int newD, queue<pair<Point, int>>&q) {
    if(x < 0 || y < 0 || x >= gridSize || y >= gridSize || !available[x][y])
        return;
    available[x][y] = false;
    q.push(make_pair(Point(x, y), newD));
}

void ReadData() {
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> inputGrid[i][j];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(inputGrid[i][j] == 'r') {
                if(initBoatPos.x == -1) {
                    int last = j;
                    for(int k = j + 1; k < n; k++)
                        if(inputGrid[i][k] == 'r')
                            last = k;
                    initBoatPos = Point(i, (last + j) >> 1);
                }
                boat.push_back(Point(i - initBoatPos.x, j - initBoatPos.y));
            }
        }
    }
    if(symmetricVertically(boat)) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                v[j][i] = inputGrid[i][j];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                inputGrid[i][j] = v[i][j];
    }
    boat.clear();
    initBoatPos = Point(-1, -1);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(inputGrid[i][j] == 'r') {
                if(initBoatPos.x == -1) {
                    int last = j;
                    for(int k = j + 1; k < n; k++)
                        if(inputGrid[i][k] == 'r')
                            last = k;
                    initBoatPos = Point(i, (last + j) / 2);
                }
                boat.push_back(Point(i - initBoatPos.x, j - initBoatPos.y));
                if(boat.back().y < leftmost.y)
                    leftmost = boat.back();
                if(boat.back().y > rightmost.y)
                    rightmost = boat.back();
                bottomOffset = max(bottomOffset, i - initBoatPos.x);
            }
        }
    }
    leftmost.x = rightmost.x = bottomOffset / 2;
    boatSize = max(bottomOffset, abs(leftmost.y) + abs(rightmost.y)) + 5;
    initBoatPos.x += boatSize;
    initBoatPos.y += boatSize;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            obstacle[i + boatSize][j + boatSize] = inputGrid[i][j] == 'X';
    gridSize = n + 2 * boatSize;
}
