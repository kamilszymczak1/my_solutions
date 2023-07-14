#include <algorithm>
#include <cstdio>
#include <deque>
using namespace std;
const int MAX_N = 1000007;
int d[MAX_N], dp[MAX_N], n, q;

class PriorityQueue {
private:
    deque<pair<int, int>>q;
public:
    void insert(int val) {
        int count = 1;
        while(!q.empty() && d[q.back().first] <= d[val]) {
            count += q.back().second;
            q.pop_back();
        }
        q.push_back(make_pair(val, count));
    }
    int front() {
        return q.front().first;
    }
    void pop() {
        if(q.front().second == 1)
            q.pop_front();
        else
            q.front().second--;
    }
    bool empty() {
        return q.empty();
    }
    void clear() {
        q.clear();
    }
};

int Solve(int k) {
    dp[0] = 0;
    PriorityQueue q1, q2;
    q1.insert(0);
    int q1dpVal = 0;
    for(int i = 1; i < n; i++) {
        int x = q1.front();
        
        dp[i] = dp[x] + (d[x] <= d[i]);
        if(i - k >= 0) {
            if(dp[i - k] == q1dpVal)
                q1.pop();
            if(dp[i - k] == q1dpVal + 1)
                q2.pop();
        }
        if(dp[i] == q1dpVal) {
            q1.insert(i);
        }
        if(dp[i] == q1dpVal + 1) {
            q2.insert(i);
        }
        if(dp[i] == q1dpVal + 2 || q1.empty()) {
            swap(q1, q2);
            q2.clear();
            if(dp[i] != q1dpVal + 1)
                q2.insert(i);
            q1dpVal++;
        }
    }
    return dp[n - 1];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &d[i]);
    int k, q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &k);
        printf("%d\n", Solve(k));
    }
    return 0;
}
