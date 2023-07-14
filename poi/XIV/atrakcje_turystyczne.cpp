#include <iostream>
#include <vector>
#include <stack>
#include <set>

#define MAX_N 20000
#define MAX_K 20
#define inf (1 << 30)

#define layerSize 184756

using namespace std;

struct Edge {
    int16_t to, cost;
    Edge(int16_t a, int16_t b) {
        to = a;
        cost = b;
    }
};

struct Path {
    int32_t dist, set;
    int16_t end;
    Path() {}
    Path(int32_t a, int16_t b, int32_t c) {
        set = a;
        end = b;
        dist = c;
    }
};

//---graph---

vector<Edge>graph[MAX_N];
int32_t dist[MAX_N + 10];
int32_t n, m;

//--dijkstra--
void Dijkstra(int32_t beg);

//--heap for dijkstra--

int32_t heap[MAX_N + 10];
int32_t posInHeap[MAX_N + 10];
int32_t heapTail = 1;

int32_t ExtractTop();
void PushDown(int32_t x);
void ChangeInHeap(int32_t node, int32_t newd);
void PushUp(int32_t x);

//--Path list--
int32_t head = 0;
Path paths[layerSize * 10];

//--sets--
vector<int32_t>sets[MAX_K + 1];


//--others--
int32_t k;
int32_t positions[1 << MAX_K]; //position of every set in minDist[][]
int32_t minDist[layerSize][MAX_K]; //minDist for every set 
bool used[layerSize]; //used[i] == true if there exist such j that minDist[i][j] != inf
int32_t d[MAX_K][MAX_K + 1];
int32_t need[MAX_K + 1];
void ReadData();
void CalcD();
int64_t FindResult();


int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    for(int32_t i = 0; i < (1 << k); i++)
        sets[__builtin_popcount(i)].push_back(i);
    
    CalcD();
    
    int64_t result = (k == 0 ? dist[n - 1] : FindResult());
    
    cout << result << "\n";
    
    return 0;
}

int64_t FindResult() {
    
    for(int16_t z = 1; z < k; z++) {
        
        for(int32_t mask : sets[z]) {
            
            if(!used[positions[mask]])
                continue;
            
            for(int16_t j = 0; j < k; j++) {
                
                if(((mask & (1 << j)) != 0) || ((mask & need[j]) != need[j]))
                    continue;
                
                int32_t minD = inf;
                
                for(int16_t y = 0; y < k; y++)
                    minD = min(minD, minDist[positions[mask]][y] + d[j][y]);
                
                if(minD != inf)
                    paths[head++] = Path(mask | (1 << j), j, minD);
                
            }
        }
  
        for(int32_t i = 0; i < sets[z + 1].size(); i++) {
            positions[sets[z + 1][i]] = i;
            used[i] = false;
        }   
        
        for(int32_t i = 0; i < head; i++)
            used[positions[paths[i].set]] = true;
        
        for(int32_t i = 0; i < sets[z + 1].size(); i++)
            if(used[i])
                for(int16_t j = 0; j < k; j++)
                    minDist[i][j] = inf;
            
        for(int32_t i = 0; i < head; i++)
            minDist[positions[paths[i].set]][paths[i].end] = paths[i].dist;
           
        if(z != k - 1)
            head = 0;
    }
    
    int32_t result = inf;
    
    for(int32_t i = 0; i < head; i++) {
        Path p = paths[i];
        result = min(result, p.dist + d[p.end][k]);
    }    
    
    return result;
}

void ReadData() {
    int32_t a, b, c;
    cin >> n >> m >> k;
    for(int32_t i = 0; i < m; i++) {
        cin >> a >> b >> c;
        graph[a - 1].push_back(Edge(b - 1, c));
        graph[b - 1].push_back(Edge(a - 1, c));
    }
    cin >> c;
    for(int32_t i = 0; i < c; i++) {
        cin >> a >> b;
        need[b - 2] |= (1 << (a - 2));
    }
}

void CalcD() {
    
    for(int32_t i = 0; i < sets[1].size(); i++) {
        positions[sets[1][i]] = i;
        for(int j = 0; j < k; j++)
            minDist[i][j] = inf;
    }
        
    Dijkstra(0);
    for(int16_t i = 0; i < k; i++)
        if(need[i] == 0)
            minDist[positions[1 << i]][i] = dist[i + 1], used[positions[1 << i]] = true;
    
    for(int16_t i = 1; i < k + 1; i++) {
        Dijkstra(i);
        for(int16_t j = 1; j < k + 1; j++)
            d[i - 1][j - 1] = dist[j];
        d[i - 1][k] = dist[n - 1];
    }
}

void Dijkstra(int32_t beg) {
    fill(dist, dist + n, inf);
    dist[beg] = 0;
    posInHeap[beg] = heapTail = 1;
    heap[heapTail++] = beg;
    for(int32_t i = 0; i < n; i++) {
        if(i != beg) {
            posInHeap[i] = heapTail;
            heap[heapTail++] = i;
        }
    }
    
    for(int32_t i = 0; i < n; i++) {
        int32_t x = ExtractTop();
        for(Edge e : graph[x])
            if(dist[x] + e.cost < dist[e.to])
                ChangeInHeap(e.to, dist[x] + e.cost);
    }
}

void ChangeInHeap(int32_t node, int32_t newd) {
    int32_t pos = posInHeap[node];
    dist[node] = newd;
    PushUp(pos);
}

int32_t ExtractTop() {
    swap(heap[1], heap[--heapTail]);
    posInHeap[heap[1]] = 1;
    PushDown(1);
    return heap[heapTail];
}

void PushDown(int32_t x) {
    int32_t left = x * 2;
    int32_t right = x * 2 + 1;
    int32_t lowest = x;
    
    if(left < heapTail && dist[heap[left]] < dist[heap[lowest]])
        lowest = left;
    if(right < heapTail && dist[heap[right]] < dist[heap[lowest]])
        lowest = right;
    
    if(lowest != x) {
        posInHeap[heap[x]] = lowest;
        posInHeap[heap[lowest]] = x;
        swap(heap[x], heap[lowest]);
        PushDown(lowest);
    }
}

void PushUp(int32_t x) {
    if(x == 1)
        return;
    if(dist[heap[x / 2]] > dist[heap[x]]) {
        posInHeap[heap[x / 2]] = x;
        posInHeap[heap[x]] = x / 2;
        swap(heap[x / 2], heap[x]);
        PushUp(x / 2);
    }
}
