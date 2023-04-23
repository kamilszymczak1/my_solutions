#include <iostream>
#include <stack>
#include <queue>
using namespace std;
const int K = 26, MAX_N = 100;
struct Node {
    Node *child[K], *jump;
    bool visited;
    stack<int>s;
    Node() : visited(false) {
        for(int i = 0; i < K; i++)
            child[i] = NULL;
    }
};

Node *root = new Node();
stack<Node*>level[MAX_N];
bool result[MAX_N];
int maxLevel = 0;

void AddPattern(string &pattern, int index) {
    Node *current = root;
    int len = pattern.size();
    for(int i = 0; i < len; i++) {
        if(current -> child[pattern[i] - 'a'] == NULL) {
            current -> child[pattern[i] - 'a'] = new Node();
            level[i].push(current -> child[pattern[i] - 'a']);
            maxLevel = max(maxLevel, i);
        }
        current = current -> child[pattern[i] - 'a'];
    }
    current -> s.push(index);
}

void CalcJump() {
    root -> jump = NULL;
    queue<Node*>q;
    for(q.push(root); !q.empty(); q.pop()) {
        Node *n = q.front();
        for(int i = 0; i < K; i++) {
            if(n -> child[i] != NULL) {
                Node *current = n -> jump;
                while(current != NULL && current -> child[i] == NULL)
                    current = current -> jump;
                n -> child[i] -> jump = current == NULL ? root : current -> child[i];
                q.push(n -> child[i]);
            }
        }
    }
}

void Match(string &text) {
    Node *current = root;
    for(char c : text) {
        while(current != NULL && current -> child[c - 'a'] == NULL)
            current = current -> jump;
        current = current == NULL ? root : current -> child[c - 'a'];
        current -> visited = true;
    }
}

void GetResult() {
    for(int i = maxLevel; i >= 0; i--) {
        for(; !level[i].empty(); level[i].pop()) {
            Node *n = level[i].top();
            if(n -> visited && n -> jump != NULL)
                n -> jump -> visited = true;
            for(; !n -> s.empty(); n -> s.pop())
                result[n -> s.top()] = n -> visited;
        }
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    string text, pattern;
    int k;
    cin >> text >> k;
    for(int i = 0; i < k; i++) {
        cin >> pattern;
        AddPattern(pattern, i);
    }
    CalcJump();
    Match(text);
    GetResult();
    for(int i = 0; i < k; i++)
        cout << (result[i] ? "YES" : "NO") << '\n';
    return 0;
}
