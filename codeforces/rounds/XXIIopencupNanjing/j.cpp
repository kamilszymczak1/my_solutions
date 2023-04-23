#include <cstdio>
#include <set>
#include <map>
#include <vector>

using namespace std;

const long long M = 1'000'000'001;

vector<int>PrimeDivisors (int x) {
    int i = 2;
    vector<int>result;
    while(i * i <= x) {
        if(x % i == 0) {
            result.push_back(i);
            while(x % i == 0)
                x /= i;
        }
        i++;
    }
    if(x != 1)
        result.push_back(x);
    return result;
}

void TestCase() {
    int a, b; scanf("%d%d", &a, &b);
    if(a > b)
        swap(a, b);
    vector<int>div = PrimeDivisors(b - a);
    map<long long, int>m;
    m[a * M + b] = 0;
    set<pair<int, long long>>s;
    s.insert(make_pair(0, a * M + b));
    int result = M;
    while(!s.empty()) {
        auto [c, x] = *s.begin();
        s.erase(s.begin());
        if(m[x] != c)
            continue;
        a = x / M, b = x % M;
        result = min(result, a - 1 + c);
        if(a == 1)
            break;
        for(int d : div) {
            if(a % d != b % d)
                continue;
            if(a % d <= d - a % d) {
                int newA = a / d, newB = b / d;
                long long newX = newA * M + newB;
                long long newC = c + a % d + 1;
                if(m.find(newX) == m.end() || m[newX] > newC) {
                    m[newX] = newC;
                    s.insert(make_pair(newC, newX));
                }
            }
            
            if(d - a % d <= a % d) {
                int newA = a / d + 1, newB = b / d + 1;
                long long newX = newA * M + newB;
                long long newC = c + d - a % d + 1;
                if(m.find(newX) == m.end() || m[newX] > newC) {
                    m[newX] = newC;
                    s.insert(make_pair(newC, newX));
                }
            }
        }
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
