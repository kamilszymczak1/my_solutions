#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
using namespace std;
class Tree {
private:
    int leafCount;
    vector<long long>values;
public:
    Tree(int n) {
        leafCount = 1;
        while(leafCount < n)
            leafCount <<= 1;
        values.reserve(leafCount << 1);
        values.resize(leafCount << 1, 0);
    }
    void Add(int x, int value) {
        values[x += leafCount] += value;
        while(x > 1) {
            x >>= 1;
            values[x] = values[x << 1] + values[(x << 1) + 1];
        }
    }
    long long GetSum(int a, int b) {
        long long result = values[a + leafCount] + (a == b ? 0 : values[b + leafCount]);
        for(a += leafCount, b += leafCount; (a >> 1) != (b >> 1); a >>= 1, b >>= 1) {
            if(!(a & 1))
                result += values[a + 1];
            if(b & 1)
                result += values[b - 1];
        }
        return result;
    }
};

class Scaler {
private:
    vector<int>values;
    map<int, int>m;
    int size;
public:
    Scaler() {
        size = 0;
    }
    void AddValue(int x) {
        values.push_back(x);
    }
    void Scale() {
        sort(values.begin(), values.end());
        size = 0;
        for(int x : values)
            if(m[x] == 0)
                m[x] = ++size;
    }
    int GetScaled(int x) {
        return m[x] - 1;
    }
    int Size() {
        return size;
    }
    int ScaledUpperBound(int x) {
        auto it = m.upper_bound(x);
        if(it == m.end())
            return size;
        return it -> second - 1;
    }
};

class Solver {
private:
    Scaler *S;
    Tree *T1, *T2;
    vector<int>A;
    vector<tuple<int, int, int>>queries;
    void Update(int x, int a) {
        int scaled = S -> GetScaled(A[x]);
        T1 -> Add(scaled, -A[x]);
        T2 -> Add(scaled, -1);
        scaled = S -> GetScaled(a);
        T1 -> Add(scaled, a);
        T2 -> Add(scaled, 1);
        A[x] = a;
    }
    bool Query(long long c, long long s) {
        long long required = s * c;
        long long possible = T1 -> GetSum(0, S -> ScaledUpperBound(s) - 1);
        possible += T2 -> GetSum(S -> ScaledUpperBound(s), S -> Size()) * s;
        return possible >= required;
    }
public:
    Solver(int n, int m) {
        S = new Scaler();
        S -> AddValue(0);
        queries.reserve(m);
        A.reserve(n);
        A.resize(n, 0);
    }
    void AddQuery(int x, int y, int z) {
        if(x == 0) {
            queries.emplace_back(make_tuple(0, y - 1, z));
            S -> AddValue(z);
        } else {
            queries.emplace_back(make_tuple(1, y, z));
        }
    }
    vector<bool> Solve() {
        S -> Scale();
        T1 = new Tree(S -> Size() + 1);
        T2 = new Tree(S -> Size() + 1);
        vector<bool>result;
        int x, y, z;
        for(tuple<int, int, int>t : queries) {
            tie(x, y, z) = t;
            if(x == 0) {
                Update(y, z);
            } else {
                result.push_back(Query(y, z));
            }
                
        }
        return result;
    }
};
int main() {
    ios_base::sync_with_stdio(0);
    int n, m, x, y;
    char c;
    cin >> n >> m;
    Solver solver(n, m);
    while(m--) {
        cin >> c >> x >> y;
        solver.AddQuery(c == 'Z', x, y);
    }
    vector<bool>ans = solver.Solve();
    for(bool b : ans)
        cout << (b ? "TAK" : "NIE") << '\n';
    
    return 0;
}
