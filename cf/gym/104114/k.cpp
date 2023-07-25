#include <iostream>
#include <vector>
    
using namespace std;
    
const long long inf = 1ll << 60;
    
const int MAX_N = 100'007;
    
vector<pair<int, long long>>adj[MAX_N];
long long min_dist[MAX_N];
long long answer[MAX_N];
    
struct query {
    int a, b, id;
    query(int _a, int _b, int _id) : a(_a), b(_b), id(_id) {}
};
    
int heap[MAX_N], r_heap[MAX_N];
int heap_size = 0;
    
void heap_restore_up(int x) {
    while(x > 1 && min_dist[heap[x / 2]] > min_dist[heap[x]]) {
        swap(heap[x / 2], heap[x]);
        r_heap[heap[x / 2]] = x / 2;
        r_heap[heap[x]] = x;
        x /= 2;
    }
}
    
void heap_restore_down(int x) {
    int next = x;
    do {
        x = next;
        if(2 * x <= heap_size && min_dist[heap[2 * x]] < min_dist[heap[next]]) {
            next = 2 * x;
        }
        if(2 * x + 1 <= heap_size && min_dist[heap[2 * x + 1]] < min_dist[heap[next]]) {
            next = 2 * x + 1;
        }
        
        swap(heap[next], heap[x]);
        r_heap[heap[next]] = next;
        r_heap[heap[x]] = x;
        
    } while(next != x);
}
    
void heap_push(int x) {
    heap[++heap_size] = x;
    r_heap[x] = heap_size;
    heap_restore_up(heap_size);
}
    
void heap_add(int x) {
    heap[++heap_size] = x;
    r_heap[x] = heap_size;
}
    
void heap_build() {
    for(int i = heap_size; i > 0; i--) {
        heap_restore_down(i);
    }
}
    
int heap_top() { return heap[1]; }
    
void heap_pop() {
    swap(heap[1], heap[heap_size--]);
    if(heap_size > 0) {
        r_heap[heap[1]] = 1;
        heap_restore_down(1);
    }
}
    
void heap_set_min(int x, long long new_value) {
    min_dist[x] = min(min_dist[x], new_value);
    heap_restore_up(r_heap[x]);
}
    
void go(int lo, int hi, vector<query>&queries) {
    
    if(queries.empty())
        return;
    
    int mid = (lo + hi) / 2;
    
    int l = max(lo, mid - 4);
    int r = min(hi - 1, mid + 5);
    
    vector<query>left_q, right_q;
    for(query q : queries) {
        if(q.b < l) {
            left_q.push_back(q);
        } else if(q.a > r) {
            right_q.push_back(q);
        }
    }
    
    if(lo < l) {
        go(lo, l, left_q);
    } if(r + 1 < hi) {
        go(r + 1, hi, right_q);
    }
    
    for(int source = l; source <= r; source++) {
        
        for(int i = lo; i < hi; i++) {
            min_dist[i] = i == source ? 0 : inf;
            heap_add(i);
        }
        
        heap_build();
        
        while(heap_size > 0) {
            int x = heap_top();
            heap_pop();
            for(auto [y, w] : adj[x]) {
                if(y < lo || y >= hi)
                    continue;
                if(min_dist[y] > min_dist[x] + w) {
                    heap_set_min(y, min_dist[x] + w);
                }
            }
        }
        
        for(query q : queries) {
            if(q.a >= lo && q.b < hi) {
                answer[q.id] = min(answer[q.id], min_dist[q.a] + min_dist[q.b]);
            }
            
        }
    }
    
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, q; cin >> n >> m >> q;
    for(int i = 0; i < m; i++) {
        int a, b, w; cin >> a >> b >> w;
        adj[a - 1].emplace_back(b - 1, w);
        adj[b - 1].emplace_back(a - 1, w);
    }
    
    vector<query>queries;
    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        queries.emplace_back(min(a, b) - 1, max(a, b) - 1, i);
        answer[i] = inf;
    }
    
    go(0, n, queries);
    
    for(int i = 0; i < q; i++)
        cout << (answer[i] == inf ? -1ll : answer[i]) << '\n';
    
    return 0;
}
