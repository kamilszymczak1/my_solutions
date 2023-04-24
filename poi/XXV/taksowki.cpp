#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX_N = 500007;
const long long inf = 1000000000;

long long GCD(long long x, long long y) {
    while(y != 0) {
        long long z = x % y;
        x = y;
        y = z;
    }
    return x;
}

struct Fraction {
    long long x, y;
    Fraction() : x(1), y(inf) {}
    Fraction(long long _x, long long _y) : x(_x), y(_y) {}
    void reduce() {
        long long gcd = GCD(x, y);
        x /= gcd; y /= gcd;
    }
};

bool operator< (Fraction A, Fraction B) {
    return A.x * B.y < B.x * A.y;
}

struct Interval {
    Fraction left, right;
    bool empty;
    Interval() {}
    Interval(Fraction _left, Fraction _right, bool _empty = false) {
        left = _left; right = _right;
        empty = _empty;
    }
};

const Interval EmptyInterval = Interval(Fraction(), Fraction(), true);
const Interval InfInterval = Interval(Fraction(1, inf), Fraction(inf, 1));
const int leafCount = 1 << 19;
Interval tree[leafCount << 1];
long long s[MAX_N], c[MAX_N];
int n, q, order[MAX_N];

Interval Merge(Interval A, Interval B) {
    if(B.left < A.left) {
        Interval C = A;
        A = B;
        B = C;
    }
    if(A.empty || B.empty || A.right < B.left)
        return EmptyInterval;
    Interval result = Interval(B.left, B.right < A.right ? B.right : A.right);
    return result; 
}

Interval LessInterval(int a, int b) {
    if(s[a] <= s[b] && c[a] <= c[b])
        return InfInterval;
    if(s[a] >= s[b] && c[a] >= c[b])
        return EmptyInterval;
    Fraction MeetPoint(abs(s[b] - s[a]), abs(c[b] - c[a]));
    if(s[a] < s[b])
        return Interval(Fraction(1, inf), MeetPoint);
    return Interval(MeetPoint, Fraction(inf, 1));
}

void Insert(int x, Interval A) {
    tree[x + leafCount] = A;
    for(x = (x + leafCount) >> 1; x; x >>= 1)
        tree[x] = Merge(tree[x << 1], tree[(x << 1) + 1]);
}

void Swap(int a, int b) {
    swap(order[a], order[b]);
    if(a != 0) {
        Insert(a - 1, LessInterval(order[a - 1], order[a]));
    }
    if(a != n - 1) {
        Insert(a, LessInterval(order[a], order[a + 1]));
    }
    if(b != 0) {
        Insert(b - 1, LessInterval(order[b - 1], order[b]));
    }
    if(b != n - 1) {
        Insert(b, LessInterval(order[b], order[b + 1]));
    }
}

void Answer() {
    if(tree[1].empty) {
        printf("NIE\n");
    } else {
        tree[1].left.reduce();
        printf("%lld/%lld\n", tree[1].left.x, tree[1].left.y);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &s[i], &c[i]);
    for(int i = 0; i < n; i++) {
        scanf("%d", &order[i]);
        order[i]--;
    }
    for(int i = 0; i < n - 1; i++)
        tree[i + leafCount] = LessInterval(order[i], order[i + 1]);
    for(int i = n - 1; i < leafCount; i++)
        tree[i + leafCount] = InfInterval;
    for(int i = leafCount - 1; i; i--)
        tree[i] = Merge(tree[i << 1], tree[(i << 1) + 1]);
    Answer();
    scanf("%d", &q);
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        Swap(a - 1, b - 1);
        Answer();
    }
    
    return 0;
}
