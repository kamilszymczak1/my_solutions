#include <cstdio>
#include <stack>

using namespace std;

const int MAX_N = 2007;

int n, x1, y1, x2, y2, ans = false, lastWrong[MAX_N];
int l[MAX_N], r[MAX_N];
long long k, a[MAX_N][MAX_N], s[MAX_N][MAX_N];

void Check1D() {
    for(int i = 1; i <= n; i++) {
        int end = 0;
        long long sum = 0;
        for(int beg = 1; beg <= n; beg++) {
            while(end < n && sum < k) {
                end++;
                sum += a[i][end];
            }
            if(k <= sum && sum <= k * 2) {
                x1 = beg; x2 = end;
                y1 = y2 = i;
                ans = true;
            }
            sum -= a[i][beg];
        }
    }
}

long long Sum(int a1, int b1, int a2, int b2) {
    return s[a2][b2] - s[a2][b1 - 1] - s[a1 - 1][b2] + s[a1 - 1][b1 - 1];
}

int main() {
    scanf("%lld%d", &k, &n);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    
    Check1D();
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
        }
    }
    
    for(int i = 1; i <= n; i++)
        lastWrong[i] = 0;
    for(int i = 1; i <= n && ans == false; i++) {
        for(int j = 1; j <= n; j++) {
            if(a[j][i] > 2 * k) {
                lastWrong[j] = i;
            }
        }
        stack<pair<int, int>>s;
        s.push(make_pair(-1, 0));
        for(int j = 1; j <= n; j++) {
            int h = i - lastWrong[j];
            while(s.top().first >= h)
                s.pop();
            l[j] = s.top().second + 1;
            s.push(make_pair(h, j));
        }
        while(!s.empty())
            s.pop();
        s.push(make_pair(-1, n + 1));
        for(int j = n; j >= 1; j--) {
            int h = i - lastWrong[j];
            while(s.top().first >= h)
                s.pop();
            r[j] = s.top().second - 1;
            s.push(make_pair(h, j));
        }
        
        for(int j = 1; j <= n && ans == false; j++) {
            if(lastWrong[j] == i)
                continue;
            long long sum = Sum(l[j], lastWrong[j] + 1, r[j], i);
            if(sum >= k) {
                for(int t = i; t > lastWrong[j]; t--) {
                    sum = Sum(l[j], lastWrong[j] + 1, r[j], t);
                    if(k <= sum && sum <= 2 * k) {
                        x1 = lastWrong[j] + 1; x2 = t;
                        y1 = l[j]; y2 = r[j];
                        ans = true;
                        break;
                    }
                }
            }
        }
    }
    
    if(ans) {
        printf("%d %d %d %d\n", x1, y1, x2, y2);
    } else {
        printf("NIE\n");
    }
    
}
