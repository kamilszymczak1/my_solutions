#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int B = 17;

int l, r, X[1 << B];

struct Node {
        int left, right;
        Node() : left(-1), right(-1) {}
} nodes[(1 << B) * B];
int head;

void Clear() {
    head = 1;
    nodes[0].left = nodes[0].right = -1;
}

int NewNode() {
    nodes[head].left = nodes[head].right = -1;
    return head++;
}

void Add(int x) {
    int node = 0;
    for(int i = B - 1; i >= 0; i--) {
        if(x & (1 << i)) {
            if(nodes[node].right == -1) {
                int t = NewNode();
                nodes[node].right = t;
            }
            node = nodes[node].right;
        } else {
            if(nodes[node].left == -1) {
                int t = NewNode();
                nodes[node].left = t;
            }
            node = nodes[node].left;
        }
    }
}

int FindMax(int x) {
    int node = 0, result = 0;
    for(int i = B - 1; i >= 0; i--) {
        if(x & (1 << i)) {
            if(nodes[node].left == -1) {
                node = nodes[node].right;
            } else {
                node = nodes[node].left;
                result |= 1 << i;
            }
        } else {
            if(nodes[node].right == -1) {
                node = nodes[node].left;
            } else {
                node = nodes[node].right;
                result |= 1 << i;
            }
        }
    }
    return result;
}

int FindMin(int x) {
    int node = 0, result = 0;
    for(int i = B - 1; i >= 0; i--) {
        if(x & (1 << i)) {
            if(nodes[node].right == -1) {
                node = nodes[node].left;
                result |= 1 << i;
            } else {
                node = nodes[node].right;
            }
        } else {
            if(nodes[node].left == -1) {
                node = nodes[node].right;
                result |= 1 << i;
            } else {
                node = nodes[node].left;
            }
        }
    }
    return result;
}

int Check(int x) {
    if(FindMin(x) < l || FindMax(x) > r)
        return false;
    return true;
}

void TestCase() {
    Clear();
    scanf("%d%d", &l, &r);
    for(int i = l; i <= r; i++) {
        scanf("%d", &X[i - l]);
        Add(X[i - l]);
    }
    
    for(int i = 0; i < r - l + 1; i++) {
        if(Check(l ^ X[i])) {
            printf("%d\n", l ^ X[i]);
            return;
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
