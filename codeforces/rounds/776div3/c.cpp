#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Segment {
    int w, x, id;
    Segment() {}
    Segment(int _w, int _x, int _id) : w(_w), x(_x), id(_id) {}
};

bool cmpx(Segment &A, Segment &B) {
    return A.x < B.x;
}

bool cmpw(Segment &A, Segment &B) {
    return A.w < B.w;
}

void TestCase() {
    vector<Segment>t;
    int n, m; scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int x, w; scanf("%d%d", &x, &w);
        t.emplace_back(w, x, i);
    }
    sort(t.begin(), t.end(), cmpw);
    t.resize(n * 2);
    sort(t.begin(), t.end(), cmpx);
    int result = 0;
    for(int i = 0; i < n * 2; i++)
        result += t[i].w;
    printf("%d\n", result);
    for(int i = 0; i < n; i++)
        printf("%d %d\n", t[i].id + 1, t[2 * n - i - 1].id + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
