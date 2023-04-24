#include <iostream>
#include <deque>

using namespace std;

const int MAX_N = 100000, inf = 2000000100, SIZE = 2200007, LEFT = 0, RIGHT = 1;

struct Point {
    int layer, row, index;
    Point(int _layer, int _row, int _index) : layer(_layer), row(_row), index(_index) {}
};

int holes[SIZE], dist[2][SIZE], amount[MAX_N], first[MAX_N];
int n, X, z;

void ReadData(), BFS(), LeftInRow(Point p, deque<Point>&q), GoDown(Point p, deque<Point>&q), GoUp(Point p, deque<Point>&q);
int FirstToLeft(int row, int pos);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    ReadData();
    BFS();
    
    int p;
    for(int i = 0; i < z; i++) {
        cin >> p;
        cout << dist[RIGHT][first[p - 1]] << "\n";
    }
    
    return 0;
}

void BFS() {
    deque<Point>q;
    for(int i = 0; i < n; i++)
        q.push_front(Point(LEFT, i, amount[i] - 1));
    
    while(!q.empty()) {
        Point p = q.front();
        q.pop_front();
        LeftInRow(p, q);
        GoDown(p, q);
        GoUp(p, q);
    }
}

void LeftInRow(Point p, deque<Point>&q) {
    
    if(p.layer == LEFT && dist[RIGHT][first[p.row] + p.index - 1] > dist[LEFT][first[p.row] + p.index]) {
        dist[RIGHT][first[p.row] + p.index - 1] = dist[LEFT][first[p.row] + p.index];
        if(p.index != 1)
            q.push_front(Point(RIGHT, p.row, p.index - 1));
    }
    
    if(p.layer == RIGHT && dist[LEFT][first[p.row] + p.index] > dist[RIGHT][first[p.row] + p.index] + 1) {
        dist[LEFT][first[p.row] + p.index] = dist[RIGHT][first[p.row] + p.index] + 1;
        q.push_back(Point(LEFT, p.row, p.index));
    }
}

void GoDown(Point p, deque<Point>&q) {
    if(p.layer == LEFT || p.row == n - 1)
        return;
    
    int firstToRight = FirstToLeft(p.row + 1, holes[first[p.row] + p.index]) + 1;
    if(dist[LEFT][firstToRight] > dist[RIGHT][first[p.row] + p.index] + 1) {
        dist[LEFT][firstToRight] = dist[RIGHT][first[p.row] + p.index] + 1;
        q.push_back(Point(LEFT, p.row + 1, firstToRight - first[p.row + 1]));
    }
}

void GoUp(Point p, deque<Point>&q) {
    if(p.layer == RIGHT || p.row == 0)
        return;
    int firstToLeft = FirstToLeft(p.row - 1, holes[first[p.row] + p.index]);
    while(firstToLeft > first[p.row - 1] && holes[firstToLeft] >= holes[first[p.row] + p.index - 1]) {
        if(dist[LEFT][firstToLeft] > dist[LEFT][first[p.row] + p.index]) {
            dist[LEFT][firstToLeft] = dist[LEFT][first[p.row] + p.index];
            q.push_front(Point(LEFT, p.row - 1, firstToLeft - first[p.row - 1]));
        }
        firstToLeft--;
    }
}

int FirstToLeft(int row, int pos) {
    int beg = first[row], end = first[row] + amount[row];
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if(holes[mid] >= pos)
            end = mid - 1;
        else
            beg = mid + 1;
    }
    return min(max(first[row], end), first[row] + amount[row] - 1);
}

void ReadData() {
    cin >> n >> X >> z;
    int sum = 0;
    X = X + 10;
    
    for(int i = 0; i < n; i++) {
        first[i] = sum;
        cin >> amount[i];
        amount[i] += 2;
        for(int j = 0; j < 2; j++)
            fill(dist[j] + sum, dist[j] + sum + amount[i], inf);
        holes[sum] = 0;
        for(int j = 1; j < amount[i] - 1; j++)
            cin >> holes[sum + j];
        holes[sum + amount[i] - 1] = X;
        dist[LEFT][sum + amount[i] - 1] = 0;
        sum += amount[i];
    }
}
