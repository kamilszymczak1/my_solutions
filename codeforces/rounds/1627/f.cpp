#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Point {
    int row, column;
    Point(int _row, int _column) : row(_row), column(_column) {}
    Point() {}
};

vector<int>dist;
struct Compare {
    inline bool operator() (const int &a, const int &b) const {
        if(dist[a] == dist[b])
            return a < b;
        return dist[a] < dist[b];
    }
};

void Dijkstra(vector<vector<pair<int, int>>>&adj) {
    int n = adj.size();
    set<int, Compare>s;
    for(int i = 0; i < n; i++)
        s.insert(i);
    while(!s.empty()) {
        int x = *s.begin();
        s.erase(x);
        for(auto [y, w] : adj[x]) {
            if(dist[y] > dist[x] + w) {
                s.erase(s.find(y));
                dist[y] = dist[x] + w;
                s.insert(y);
            }
        }
    }
}

int Solve(int k, vector<pair<Point, Point>>P) {
    int H = k / 2 + 1, W = k + 1;
    vector<vector<pair<int, int>>>adj(H * W);
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(i != 0) adj[i * W + j].emplace_back(i * W + j - W, 0);
            if(i != H - 1) adj[i * W + j].emplace_back(i * W + j + W, 0);
            if(j != 0) adj[i * W + j].emplace_back(i * W + j - 1, 0);
            if(j != W - 1) adj[i * W + j].emplace_back(i * W + j + 1, 0);
        }
    }
    int n = P.size();
    for(int i = 0; i < n; i++) {
        if(P[i].first.row > P[i].second.row)
            swap(P[i].first, P[i].second);
        if(P[i].first.row == k / 2 && P[i].second.row == k / 2 + 1) {
            Point P1(P[i].first.row, k - P[i].first.column + 1);
            Point P2(P[i].second.row, k - P[i].second.column + 1);
            P.emplace_back(P1, P2);
        }
    }
    for(pair<Point, Point>p : P) {
        if(p.first.row > k / 2 || p.second.row > k / 2) {
            p.first.row = k - p.first.row + 1;
            p.second.row = k - p.second.row + 1;
            p.first.column = k - p.first.column + 1;
            p.second.column = k - p.second.column + 1;
        }
        int y, x;
        if(p.first.row == p.second.row) {
            int a = min(p.first.column, p.second.column);
            x = (p.first.row - 1) * W + a;
            y = p.first.row * W + a;
            
        } else {
            int a = min(p.first.row, p.second.row);
            x = a * W + p.first.column - 1;
            y = a * W + p.first.column;
        }
        for(auto &[nei, w] : adj[x]) {
            if(nei == y)
                w++;
        }
        for(auto &[nei, w] : adj[y]) {
            if(nei == x)
                w++;
        }
    }
    dist.resize(H * W);
    fill(dist.begin(), dist.end(), 1 << 30);
    for(int i = 0; i < W; i++)
        dist[i] = 0;
    for(int i = 0; i < H; i++)
        dist[i * W] = dist[i * W + W - 1] = 0;
    Dijkstra(adj);
    return (int)n - dist[H * W - k / 2 - 1];
}

void TestCase() {
    int n, k; cin >> n >> k;
    vector<pair<Point, Point>>P(n);
    for(pair<Point, Point>&p : P) {
        cin >> p.first.row >> p.first.column;
        cin >> p.second.row >> p.second.column;
    }
    int result = Solve(k, P);
    for(pair<Point, Point>&p : P) {
        swap(p.first.row, p.first.column);
        swap(p.second.row, p.second.column);
    }
    result = max(result, Solve(k, P));
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
