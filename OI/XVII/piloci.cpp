#include <algorithm>
#include <cstdio>
#include <deque>
using namespace std;
const int MAX_N = 3000007, inf = 2000000007;
int a[MAX_N], n, t;

class PriorityQueue {
private:
    deque<pair<long long, int>>q;
    int sign;
public:
    PriorityQueue(int _sign) : sign(_sign) {}
    void insert(int x) {
        int count = 1;
        while(!q.empty() && q.back().first * sign <= x * sign) {
            count += q.back().second;
            q.pop_back();
        }
        q.push_back(make_pair(x, count));
    }
    int front() {
        if(q.empty())
            return 0;
        return q.front().first;
    }
    void pop() {
        if(q.empty())
            return;
        if(q.front().second == 1)
            q.pop_front();
        else
            q.front().second--;
    }
};

int main() {
    scanf("%d%d", &t, &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    PriorityQueue maxQ(1), minQ(-1);
    int end = 0, result = 1;
    for(int beg = 0; end < n; beg++) {
        while(end < n && (max(maxQ.front(), a[end]) - min(minQ.front(), a[end]) <= t || end == beg)) {
            maxQ.insert(a[end]);
            minQ.insert(a[end]);
            end++;
        }
        result = max(result, end - beg);
        maxQ.pop();
        minQ.pop();
    }
    printf("%d\n", result);
    return 0;
}
