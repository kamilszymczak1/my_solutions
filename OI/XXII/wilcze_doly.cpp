#include <algorithm>
#include <cstdio>
#include <deque>
using namespace std;
const int MAX_N = 2000007;
long long p, w[MAX_N], plankCost[MAX_N];
class PriorityQueue {
private:
    deque<pair<long long, int>>q;
public:
    void insert(long long val) {
        int count = 1;
        while(!q.empty() && q.back().first <= val) {
            count += q.back().second;
            q.pop_back();
        }
        q.push_back(make_pair(val, count));
    }
    long long front() {
        return q.empty() ? 0 : q.front().first;
    }
    void pop() {
        if(q.front().second == 1)
            q.pop_front();
        else
            q.front().second--;
    }
};
int main() {
    int n, d;
    scanf("%lld%lld%lld", &n, &p, &d);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &w[i]);
        w[i] += w[i - 1];
    }
    for(int i = 1; i + d <= n + 1; i++)
        plankCost[i] = w[i + d - 1] - w[i - 1];
    
    PriorityQueue q;
    q.insert(plankCost[1]);
    int end = d + 1, result = d;
    for(int beg = 1; end <= n; beg++) {
        while(end <= n && w[end] - w[beg - 1] - max(q.front(), plankCost[end - d + 1]) <= p) {
            q.insert(plankCost[end - d + 1]);
            end++;
        }
        result = max(result, end - beg);
        q.pop();
    }
    printf("%d\n", result);
    return 0;
}
