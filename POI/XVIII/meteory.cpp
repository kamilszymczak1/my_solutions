#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int MAX_N = 300007;
const long long inf = 1000000007;

class Tree {
private:
    int leafCount;
    vector<long long>val;
public:
    Tree(int _n) {
        for(leafCount = 1; leafCount < _n; leafCount <<= 1) {}
        val.reserve(leafCount << 1);
        val.resize(leafCount << 1, 0);
    }
    void add(int a, int b, long long value) {
        a += leafCount;
        b += leafCount;
        val[a] = min(val[a] + value, inf);
        if(a != b)
            val[b] = min(val[b] + value, inf);
        for(;(a >> 1) != (b >> 1); a >>= 1, b >>= 1) {
            if(!(a & 1))
                val[a + 1] = min(val[a + 1] + value, inf);
            if(b & 1)
                val[b - 1] = min(val[b - 1] + value, inf);
        }
    }
    long long get(int x) {
        long long result = 0;
        for(x += leafCount; x > 0; x >>= 1)
            result += val[x];
        return result;
    }
    void fill(int value) {
        for(long long &x : val)
            x = value;
    }
};

vector<int>sectors[MAX_N];
long long required[MAX_N], result[MAX_N];
int n, m, k;

struct Update {
    int l, r;
    long long a;
    Update() {}
    Update(int _l, int _r, long long _a) : l(_l), r(_r), a(_a) {}
    void Perform(Tree &T) {
        if(l <= r) {
            T.add(l, r, a);
        } else {
            T.add(0, r, a);
            T.add(l, m - 1, a);
        }
    }
};

struct Query {
    int beg, end, country;
    Query(int _beg, int _end, int _country) : beg(_beg), end(_end), country(_country) {}
    int mid() {return (beg + end) / 2;}
    void answer() {
        result[country] = beg + 1;
    }
};

bool comp(Query a, Query b) {
    return a.mid() < b.mid();
}

long long GetCountryTotal(int country, Tree &T) {
    long long result = 0;
    for(int sector : sectors[country]) {
        result += T.get(sector);
    }
    return result;
}

Update updates[MAX_N];

void Binsearch(vector<Query>queries) {
    Tree T(m);
    while(queries.size() > 0) {
        sort(queries.begin(), queries.end(), comp);
        T.fill(0);
        vector<Query>newQueries;
        newQueries.reserve(queries.size());
        int uptd = 0;
        for(Query q : queries) {
            if(q.beg > q.end) {
                q.answer();
                continue;
            }
            while(uptd <= q.mid())
                updates[uptd++].Perform(T);
            if(GetCountryTotal(q.country, T) < required[q.country]) {
                newQueries.push_back(Query(q.mid() + 1, q.end, q.country));
            } else {
                newQueries.push_back(Query(q.beg, q.mid() - 1, q.country));
            }
        }
        swap(queries, newQueries);
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int o;
        cin >> o;
        sectors[o - 1].push_back(i);
    }
    for(int i = 0; i < n; i++)
        cin >> required[i];
    
    
    int l, r;
    long long a;
    cin >> k;
    for(int i = 0; i < k; i++) {
        cin >> l >> r >> a;
        updates[i] = Update(l - 1, r - 1, a);
    }
    
    vector<Query>queries;
    for(int i = 0; i < n; i++)
        queries.push_back(Query(0, k, i));
    
    Binsearch(queries);
    
    for(int i = 0; i < n; i++) {
        if(result[i] == k + 2)
            cout << "NIE\n";
        else
            cout << result[i] << '\n';
    }
    
    
    return 0;
}
