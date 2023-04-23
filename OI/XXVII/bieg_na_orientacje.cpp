#include <cstdio>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

const int MAX_N = 300'007;

struct SegTree {
    vector<pair<int, int>>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2, make_pair(-1, 0));
        for(int i = leafCount; i < leafCount * 2; i++)
            values[i].second = i - leafCount;
        for(int i = leafCount - 1; i; i--)
            values[i].second = values[i * 2].second;
    }
    void Insert(int x, int value) {
        values[x + leafCount].first = value;
        for(x = (x + leafCount) / 2; x; x /= 2)
            values[x] = max(values[x * 2], values[x * 2 + 1]);
    }
    pair<int, int> MaxSuffix(int x) {
        pair<int, int>result = values[x + leafCount];
        for(x += leafCount; x > 1; x /= 2) {
            if(x % 2 == 0) {
                result = max(result, values[x + 1]);
            }
        }
        return result;
    }
};

struct Event {
    int x, y, z, id;
    Event() {}
    Event(int _x, int _y, int _z, int _id) : x(_x), y(_y), z(_z), id(_id) {}
    int coordinate(int i) { 
        if(i == 0)
            return x;
        if(i == 1)
            return y;
        return z;
    }
};

bool operator< (Event &A, Event &B) {
    if(A.z == B.z) {
        if(A.x == B.x) {
            if(A.y == B.y)
                return A.id < B.id;
            return A.y > B.y;
        }
        return A.x > B.x;
    }
    return A.z > B.z;
}

int n, q, d[MAX_N], currentId[MAX_N], pre[MAX_N], post[MAX_N], t = 0;
vector<int>adj[MAX_N], jump[MAX_N];
pair<int, int>h[MAX_N];
array<pair<int, int>, 3>best[MAX_N];
array<int, 3>answer[MAX_N], query[MAX_N];

int Jump(int x, int t) {
    for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
        if(i < (int)jump[x].size() && (1 << i) <= t) {
            t -= 1 << i;
            x = jump[x][i];
        }
    }
    return x;
}

int LCA(int x, int y) {
    if(d[x] < d[y])
        swap(x, y);
    x = Jump(x, d[x] - d[y]);
    if(x == y)
        return x;
    for(int i = (int)jump[x].size() - 1; i >= 0; i--) {
        if(i < (int)jump[x].size() && jump[x][i] != jump[y][i]) {
            x = jump[x][i];
            y = jump[y][i];
        }
    }
    return jump[x][0];
}

int Dist(int a, int b) {
    return d[a] + d[b] - 2 * d[LCA(a, b)];
}

void CalcHeight(int x, int p) {
    pre[x] = t++;
    if(p != 0) {
        jump[x].push_back(p);
        for(int i = 1; i <= (int)jump[x].size() && i <= (int)jump[jump[x][i - 1]].size(); i++) {
            jump[x].push_back(jump[jump[x][i -1]][i - 1]);
        }
    }
    h[x] = make_pair(0, x);
    for(int y : adj[x]) {
        if(y == p)
            continue;
        d[y] = d[x] + 1;
        CalcHeight(y, x);
        if(h[y].first + 1 > h[x].first) {
            h[x].first = h[y].first + 1;
            h[x].second = h[y].second;
        }
    }
    post[x] = t;
}

void CalcP(int x, int p, pair<int, int>above) {
    best[x][0] = make_pair(above.first + 1, above.second);
    best[x][1] = best[x][2] = make_pair(0, x);
    for(int y : adj[x]) {
        if(y == p)
            continue;
        if(h[y].first + 1 >= best[x][0].first) {
            best[x][2] = best[x][1];
            best[x][1] = best[x][0];
            best[x][0] = make_pair(h[y].first + 1, h[y].second);
        } else if(h[y].first + 1 >= best[x][1].first) {
            best[x][2] = best[x][1];
            best[x][1] = make_pair(h[y].first + 1, h[y].second);
        } else {
            best[x][2] = max(best[x][2], make_pair(h[y].first + 1, h[y].second));
        }
    }
    
    for(int y : adj[x]) {
        if(y == p)
            continue;
        CalcP(y, x, h[y].second == best[x][0].second ? best[x][1] : best[x][0]);
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    CalcHeight(1, 0);
    CalcP(1, 0, make_pair(-1, 1));
    
    vector<Event>events;
    for(int i = 1; i <= n; i++) {
        events.emplace_back(best[i][0].first, best[i][1].first, best[i][2].first, -i);
    }
    for(int i = 1; i <= q; i++) {
        answer[i] = {0, 0, 0};
        scanf("%d%d%d", &query[i][0], &query[i][1], &query[i][2]);
        vector<int>v = {query[i][0], query[i][1], query[i][2]};
        sort(v.begin(), v.end());
        if(v[2] <= v[0] + v[1] && (v[0] + v[1] + v[2]) % 2 == 0) {
            int z = (v[0] + v[1] - v[2]) / 2;
            int y = (v[0] + v[2] - v[1]) / 2;
            int x = (v[1] + v[2] - v[0]) / 2;
            events.emplace_back(x, y, z, i);
        }
    }
    
    sort(events.begin(), events.end());
    
    SegTree T(n);
    for(Event e : events) {
        if(e.id > 0) {
            pair<int, int>m = T.MaxSuffix(e.x);
            
            if(m.first < e.y)
                continue;
            
            int node = currentId[m.second]; 
            for(int i = 0; i < 3; i++) {
                int deepNode = best[node][i].second;
                int distTo = best[node][i].first;
                int requiredDist = e.coordinate(i);
                int lca = LCA(node, deepNode);
                
                if(requiredDist <= d[node] - d[lca]) {
                    answer[e.id][i] = Jump(node, requiredDist);
                } else {
                    requiredDist = d[deepNode] + d[node] - d[lca] * 2 - requiredDist;
                    answer[e.id][i] = Jump(deepNode, requiredDist);
                }
            }
            
        } else {
            if(currentId[e.x] == 0 || best[currentId[e.x]][1].first < e.y) {
                currentId[e.x] = abs(e.id);
                T.Insert(e.x, e.y);
            }
        }
    }
    
    for(int i = 1; i <= q; i++) {
        if(answer[i][0] == 0) {
            printf("NIE\n");
        } else {
            bool ok = false;
            sort(answer[i].begin(), answer[i].end());
            do {
                int a = answer[i][0], b = answer[i][1], c = answer[i][2];
                if(query[i][0] == Dist(a, b) && query[i][1] == Dist(b, c) && query[i][2] == Dist(a, c)) {
                    printf("TAK %d %d %d\n", a, b, c);
                    ok = true;
                    break;
                }
            } while(next_permutation(answer[i].begin(), answer[i].end()));
            if(!ok) {
                printf("NIE\n");
            }
        }
    }
    
    return 0;
}
