#include <iostream>
#include <vector>
#include <set>
    
using namespace std;
    
const int MAX_N = 200'007;
    
long long a[MAX_N], range[MAX_N];
    
struct cmp {
    inline bool operator() (const int &x, const int &y) const {
        if(a[x] == a[y])
            return x < y;
        return a[x] > a[y];
    }
};
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    for(int i = 0; i < n; i++)
        range[i] = 1;
    
    set<int>order_set;
    set<int, cmp>value_set;
    for(int i = 0; i < n; i++) {
        order_set.insert(i);
        value_set.insert(i);
    }
    
    long long answer = 0;
    
    for(int q = 0; q < n - 1; q++) {
        
        int x = *value_set.begin();
        auto it = order_set.upper_bound(x);
        int best_neighbour = -1;
        if(it != order_set.end())
            best_neighbour = *it;
        it--;
        if(it != order_set.begin()) {
            it--;
            if(best_neighbour == -1 || a[*it] > a[best_neighbour]) {
                best_neighbour = *it;
            }
        }
        
        long long num = range[x];
        answer += (num / 2 + num % 2) * (a[x] - a[best_neighbour]);
        range[best_neighbour] += range[x];
        value_set.erase(x);
        order_set.erase(x);
    }
    
    int x = *value_set.begin();
    
    answer += (n / 2 + n % 2) * a[x];
    
    cout << answer << '\n';
    
    return 0;
}
