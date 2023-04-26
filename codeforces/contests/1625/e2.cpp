#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

struct SegTree {
    vector<long long>values;
    int leafCount;
    SegTree() {}
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2, 0);
    }
    long long Sum(int a, int b) {
        a += leafCount; b += leafCount;
        long long result = values[a] + (a == b ? 0 : values[b]);
        for(; a / 2 != b / 2; a /= 2, b /= 2) {
            if(a % 2 == 0)
                result += values[a + 1];
            if(b % 2 == 1)
                result += values[b - 1];
        }
        return result;
    }
    void Add(int x, long long value) {
        values[x += leafCount] += value;
        for(x /= 2; x; x /= 2)
            values[x] += value;
    }
};

struct Node {
    int parent, childrenCount, childId;
    SegTree removedChildren;
    Node() : parent(-1), childrenCount(0) {}
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q; n += 2;
    vector<char>s(n);
    s[0] = '('; s[n - 1] = ')';
    vector<int>match(n, -1);
    stack<int>leftBrackets;
    
    for(int i = 1; i <= n - 2; i++) {
        cin >> s[i];
        if(s[i] == '(') {
            leftBrackets.push(i);
        } else if(!leftBrackets.empty()){
            match[i] = leftBrackets.top();
            match[leftBrackets.top()] = i;
            leftBrackets.pop();
        } else {
            s[i] = '.';
        }
    }
    
    for(; !leftBrackets.empty(); leftBrackets.pop())
        s[leftBrackets.top()] = '.';
    
    vector<Node>nodes(n);
    SegTree T(n);
    int currentNode = 0;
    
    for(int i = 1; i < n - 1; i++) {
        if(s[i] == '(') {
            nodes[i].childId = nodes[currentNode].childrenCount;
            nodes[currentNode].childrenCount++;
            nodes[i].parent = currentNode;
            currentNode = i;
        } else if(s[i] == ')') {
            long long childrenCount = nodes[currentNode].childrenCount;
            T.Add(currentNode, childrenCount * (childrenCount - 1) / 2 + 1);
            currentNode = nodes[currentNode].parent;
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            nodes[i].removedChildren = SegTree(nodes[i].childrenCount);
        }
    }
    
    while(q--) {
        int t, x, y; cin >> t >> x >> y;
        if(t == 1) {
            T.Add(x, -1);
            int parentChildrenCount = nodes[nodes[x].parent].childrenCount;
            T.Add(nodes[x].parent, -nodes[nodes[x].parent].childrenCount + 1);
            nodes[nodes[x].parent].removedChildren.Add(nodes[x].childId, 1);
            nodes[nodes[x].parent].childrenCount--;
            s[x] = s[y] = '.';
        } else {
            long long s = T.Sum(x, y);
            int p = nodes[x].parent;
            long long removed = nodes[p].removedChildren.Sum(nodes[x].childId, nodes[match[y]].childId);
            long long len = nodes[match[y]].childId - nodes[x].childId + 1 - removed;
            cout << s + len * (len - 1) / 2 << '\n';
        }
    }
    
    
    return 0;
}
