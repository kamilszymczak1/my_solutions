#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const int K = 26, MAX_N = 500007;
struct Node {
    Node *child[K], *jump;
    stack<int>s;
    int visited;
    Node() {
        for(int i = 0; i < K; i++)
            child[i] = NULL;
        visited = 0;
    }
};
Node *root = new Node();
string text, pattern;
int k, result[MAX_N], lastLevel = 0;
vector<Node*>level[MAX_N];
int main() {
    ios_base::sync_with_stdio(0);
    cin >> text >> k;
    for(int i = 0; i < k; i++) {
        cin >> pattern;
        Node *current = root;
        for(int j = 0; j < (int)pattern.size(); j++) {
            if(current -> child[pattern[j] - 'a'] == NULL) {
                current -> child[pattern[j] - 'a'] = new Node();
                level[j].push_back(current -> child[pattern[j] - 'a']);
                lastLevel = max(j, lastLevel);
            }
            current = current -> child[pattern[j] - 'a'];
        }
        current -> s.push(i);
    }
    queue<Node*>q;
    root -> jump = NULL;
    for(q.push(root); !q.empty(); q.pop()) {
        for(int i = 0; i < K; i++) {
            if(q.front() -> child[i] != NULL) {
                Node *current = q.front() -> jump;
                while(current != NULL && current -> child[i] == NULL)
                    current = current -> jump;
                q.front() -> child[i] -> jump = current == NULL ? root : current -> child[i];
                q.push(q.front() -> child[i]);
            }
        }
    }
    Node *current = root;
    for(int i = 0; i < (int)text.size(); i++) {
        while(current != NULL && current -> child[text[i] - 'a'] == NULL)
            current = current -> jump;
        current = current == NULL ? root : current -> child[text[i] - 'a'];
        current -> visited++;
    }
    for(int i = lastLevel; i >= 0; i--) {
        for(Node *n : level[i]) {
            if(n -> jump != NULL)
                n -> jump -> visited += n -> visited;
            for(; !n -> s.empty(); n -> s.pop())
                result[n -> s.top()] = n -> visited;
        }
    }
    for(int i = 0; i < k; i++)
        cout << result[i] << '\n';
    return 0;
}
