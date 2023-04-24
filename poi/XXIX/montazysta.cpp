#include <algorithm>
#include <cstdio>
#include <vector>
#include <cctype>

using namespace std;

const long long inf = 1ll << 40;

int NextInt() {
    int result = 0, c;
    do {
        c = getchar_unlocked();
    } while(!isdigit(c));
    do {
        result = result * 10 + c - '0';
        c = getchar_unlocked();
    } while(isdigit(c));
    return result;
}

void  PrintInt(int x) {
    if(x == 0) {
        putchar_unlocked('0');
        return;
    }
    int reverse = 0, zeroes = 0;
    while(x % 10 == 0) {
        x /= 10;
        zeroes++;
    }
    while(x) {
        reverse = reverse * 10 + (x % 10);
        x /= 10;
    }
    while(reverse) {
        putchar_unlocked(reverse % 10 + '0');
        reverse /= 10;
    }
    while(zeroes--)
        putchar_unlocked('0');
}



struct SegTree {
    struct Node {
        long long w, W;
        Node(long long _value) : w(_value), W(0) {}
    };
    vector<Node>nodes;
    int leafCount;
    SegTree(int _n, long long _fill) {
        for(leafCount = 1; leafCount < _n; leafCount *= 2) {}
        nodes.resize(leafCount * 2, Node(_fill));
    }
    long long GetMaxRec(int a, int b, int lo, int hi, int v) {
        if(a == lo && b == hi)
            return nodes[v].w;
        if(a >= b)
            return -inf;
        const int mid = (lo + hi) / 2;
        return max(GetMaxRec(a, min(b, mid), lo, mid, v * 2), GetMaxRec(max(a, mid), b, mid, hi, v * 2 + 1)) + nodes[v].W;
    }
    int GetMax(int a, int b) {
        return GetMaxRec(a, b + 1, 0, leafCount, 1);
    }
    void AddRec(int a, int b, int lo, int hi, int v, long long value) {
        if(a == lo && b == hi) {
            nodes[v].w += value;
            nodes[v].W += value;
            return;
        }
        if(a >= b)
            return;
        const int mid = (lo + hi) / 2;
        AddRec(a, min(b, mid), lo, mid, v * 2, value);
        AddRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
        nodes[v].w = max(nodes[v * 2].w, nodes[v * 2 + 1].w) + nodes[v].W;
    }
    void Add(int a, int b, long long value) {
        AddRec(a, b + 1, 0, leafCount, 1, value);
    }
};

struct Video {
    int deadline, time, order, id;
    Video() {}
    Video(int _deadline, int _time, int _order) : deadline(_deadline), time(_time), order(_order) {}
};

bool DeadlineCmp(Video &a, Video &b) {
    if(a.deadline == b.deadline) {
        return a.time < b.time;
    }
    return a.deadline < b.deadline;
}

bool TimeCmp(Video &a, Video &b) {
    if(a.time == b.time) {
        return a.deadline < b.deadline;
    }
    return a.time < b.time;
}

int main() {
    int n = NextInt();
    vector<Video>videos(n);
    for(int i = 0; i < n; i++) {
        videos[i].time = NextInt();
        videos[i].deadline = NextInt();
        videos[i].id = i;
    }
    
    sort(videos.begin(), videos.end(), DeadlineCmp);
    
    for(int i = 0; i < n; i++) {
        videos[i].order = i;
    }
    
    sort(videos.begin(), videos.end(), TimeCmp);
    
    SegTree T(n, -inf);
    vector<Video>placed(n, Video(-1, -1, -1));
    int result = 0;
    for(Video &v : videos) {
        T.Add(v.order, v.order, inf - v.deadline);
        if(T.GetMax(v.order, n - 1) + v.time > 0) {
            T.Add(v.order, v.order, - (inf - v.deadline));
        } else {
            T.Add(v.order, n - 1, v.time);
            result++;
            placed[v.order] = v;
        }
    }
    
    PrintInt(result);
    putchar_unlocked('\n');
    
    int _time = 1;
    for(int i = 0; i < n; i++) {
        if(placed[i].deadline != -1) {
            PrintInt(placed[i].id + 1);
            putchar_unlocked(' ');
            PrintInt(_time);
            putchar_unlocked('\n');
            _time += placed[i].time;
        }
    }
    
    return 0;
}
