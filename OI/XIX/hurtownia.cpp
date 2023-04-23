#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Tree {
private:
    vector<long long>sum;
    vector<int>lastNonNegative;
    int leafCount;
public:
    Tree(vector<long long>init) {
        for(leafCount = 1; leafCount < init.size(); leafCount <<= 1) {}
        sum.reserve(leafCount << 1);
        sum.resize(leafCount << 1, 0);
        lastNonNegative.reserve(leafCount << 1);
        lastNonNegative.resize(leafCount << 1, leafCount);
        for(int i = 0; i < init.size(); i++) {
            sum[i + leafCount] = init[i];
            lastNonNegative[i + leafCount] = (init[i] > 0 ? i : -1);
        }
        for(int i = leafCount - 1; i > 0; i--) {
            lastNonNegative[i] = max(lastNonNegative[i * 2], lastNonNegative[i * 2 + 1]);
            sum[i] = sum[i * 2] + sum[i * 2 + 1];
        }
    }
    long long Sum(int a, int b) {
        a += leafCount;
        b += leafCount;
        long long result = sum[a];
        if(a != b)
            result += sum[b];
        for(;a / 2 != b / 2; a >>= 1, b >>= 1) {
            if(!(a & 1))
                result += sum[a + 1];
            if(b & 1)
                result += sum[b - 1];
        }
        return result;
    }
    void Insert(int x, long long value) {
        x += leafCount;
        sum[x] = value;
        lastNonNegative[x] = (value > 0 ? x - leafCount : -1);
        while(x > 1) {
            x >>= 1;
            sum[x] = sum[x * 2] + sum[x * 2 + 1];
            lastNonNegative[x] = max(lastNonNegative[x * 2], lastNonNegative[x * 2 + 1]);
        }
    }
    int GetLastNonNegative(int a, int b) {
        a += leafCount;
        b += leafCount;
        int result = max(lastNonNegative[a], lastNonNegative[b]);
        for(; a / 2 != b / 2; a >>= 1, b >>= 1) {
            if(!(a & 1))
                result = max(result, lastNonNegative[a + 1]);
            if(b & 1)
                result = max(result, lastNonNegative[b - 1]);
        }
        return result;
    }
};

long long nextInt() {
    long long x; cin >> x; return x;
}

int n, m, x;
int main() {
    ios_base::sync_with_stdio(0);
    vector<long long>a;
    vector<pair<long long, int>>orders;
    n = nextInt();
    for(int i = 0; i < n; i++)
        a.push_back(nextInt());
    for(int i = 0; i < n; i++)
        orders.push_back(make_pair(nextInt(), i));
    
    sort(orders.begin(), orders.end());
    
    Tree T(a);
    vector<int>ans;
    for(pair<long long, int>p : orders) {
        long long required = p.first;
        int index = p.second;
        long long prefSum = T.Sum(0, index);
        if(prefSum >= required) {
            ans.push_back(index + 1);
            while(required > 0) {
                index = T.GetLastNonNegative(0, index);
                if(T.Sum(index, index) >= required) {
                    T.Insert(index, T.Sum(index, index) - required);
                    required = 0;
                } else {
                   required -= T.Sum(index, index);
                   T.Insert(index, 0);
                }
            }
            
        }
    }
    
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
