#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int randint(int a, int b) {
    return a + rand() % (b - a + 1);
}

struct Truck {
    int s, f, r;
    long long c;
    Truck() {}
    Truck(int _s, int _f, long long _c, int _r) : s(_s), f(_f), c(_c), r(_r) {}
};

bool Check(Truck t, vector<long long>&a, long long V) {
    long long fuel = V;
    for(int i = t.s; i < t.f; i++) {
        long long d = a[i + 1] - a[i];
        if(d * t.c > V)
            return false;
        if(fuel - d * t.c < 0) {
            if(t.r == 0)
                return false;
            t.r--;
            fuel = V;
        }
        fuel -= d * t.c;
    }
    return true;
}

int main() {
    srand(time(NULL));
    int n, m; scanf("%d%d", &n, &m);
    vector<long long>a(n);
    for(long long &x : a)
        scanf("%lld", &x);
    vector<Truck>trucks(m);
    for(int i = 0; i < m; i++) {
        int s, f, r; long long c;
        scanf("%d%d%lld%d", &s, &f, &c, &r);
        trucks[i] = Truck(s - 1, f - 1, c, r);
        swap(trucks[i], trucks[randint(0, i)]);
    }
    
    long long V = 0;
    for(int i = 0; i < m; i++) {
        if(Check(trucks[i], a, V))
            continue;
        long long beg = V + 1;
        long long end = (a[trucks[i].f] - a[trucks[i].s]) * trucks[i].c;
        while(beg <= end) {
            long long mid = (beg + end) / 2;
            if(Check(trucks[i], a, mid)) {
                end = mid - 1;
            } else {
                beg = mid + 1;
            }
        }
        V = end + 1;
    }
    printf("%lld\n", V);
    
    return 0;
}
