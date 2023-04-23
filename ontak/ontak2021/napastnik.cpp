#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

constexpr long double inf = 1e11;
constexpr long double eps = 1e-6;

struct Player {
    long long x, y, vx, vy;
    Player() {}
    Player(long long _x, long long _y, long long _vx, long long _vy) : x(_x), y(_y), vx(_vx), vy(_vy) {}
    Player operator-(const Player &other) {
        return Player(x - other.x, y - other.y, vx - other.vx, vy - other.vy);
    }
};

long double square(long double x) {
    return x * x;
}

long double f(const Player &p, long double t) {
    return square(p.x + p.vx * t) + square(p.y + p.vy * t);
}

pair<long double, long double> Solve(Player &p, long long r) {
    
    if(p.vx == 0 && p.vy == 0)
        return make_pair(-1, -1);
    
    const long double smallest = -1.0 * (p.x * p.vx + p.y * p.vy) / (p.vx * p.vx + p.vy * p.vy);
    
    if(f(p, smallest) > r * r || smallest < 0)
        return make_pair(-1, -1);
    
    long double beg = 0, end = smallest;
    
    while(end - beg > eps) {
        const long double mid = (beg + end) / 2;
        if(f(p, mid) < r * r) {
            end = mid;
        } else {
            beg = mid;
        }
    }
    
    return make_pair(beg, 2 * smallest - beg);
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    long long r; cin >> r;
    Player mainPlayer;
    cin >> mainPlayer.x >> mainPlayer.y >> mainPlayer.vx >> mainPlayer.vy;
    
    vector<pair<long double, int>>events;
    
    for(int i = 0; i < n; i++) {
        Player player;
        cin >> player.x >> player.y >> player.vx >> player.vy;
        player = player - mainPlayer;
    
        pair<long double, long double>interval = Solve(player, r);
    
        if(interval.first > 0) {
            events.emplace_back(interval.first, 0);
            events.emplace_back(interval.second, 1);
        }
    
    }
    
    sort(events.begin(), events.end());
    
    int current = 0, result = 0;
    for(const pair<long double, int>event : events) {
        if(event.second == 0) {
            current++;
        } else {
            current--;
        }
        result = max(result, current);
    }
    
    cout << result << '\n';
    
    
    return 0;
}

/*
3 2
0 0 1 1
3 0 -2 1
5 6 -3 -5
-2 -1 0 -1
*/
