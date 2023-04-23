#include <iostream>
#include <vector>
#include <stack>
#include <functional>

using namespace std;

struct Node {
    vector<int>children;
    vector<long long>childrenPref;
    int parent, childId; //what is my id at my parent's adjecency list
    long long answer;
    Node() : parent(-1), childId(-1), answer(0) {
        childrenPref.push_back(0);
    }
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
    int currentNode = 0;
    for(int i = 1; i < n - 1; i++) {
        if(s[i] == '(') {
            nodes[i].childId = nodes[currentNode].children.size();
            nodes[i].parent = currentNode;
            nodes[currentNode].children.push_back(i);
            currentNode = i;
        } else if(s[i] == ')') {
            long long childrenCount = nodes[currentNode].children.size();
            nodes[currentNode].answer += childrenCount * (childrenCount - 1) / 2 + 1;
            int parent = nodes[currentNode].parent;
            nodes[parent].answer += nodes[currentNode].answer;
            nodes[parent].childrenPref.push_back(nodes[parent].childrenPref.back() + nodes[currentNode].answer);
            currentNode = parent;
        }
    }
    
    while(q--) {
        int t, x, y; cin >> t >> x >> y;
        int p = nodes[x].parent, idx = nodes[x].childId, idy = nodes[match[y]].childId;
        long long result = nodes[p].childrenPref[idy + 1] - nodes[p].childrenPref[idx];
        cout << result + (long long)(idy - idx + 1) * (idy - idx) / 2 << '\n';
    }
    
    
    return 0;
}
