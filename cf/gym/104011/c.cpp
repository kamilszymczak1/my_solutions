#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
const int A = 26;
    
struct trie_node {
    trie_node *children[A];
    int weight;
    trie_node() {
        for(int i = 0; i < A; i++)
            children[i] = NULL;
        weight = 0;
    }
};
    
void trie_add(trie_node *v, string &s) {
    for(char c : s) {
        if(v -> children[c - 'a'] == NULL)
            v -> children[c - 'a'] = new trie_node();
        v = v -> children[c - 'a'];
    }
    v -> weight = 1;
}
    
pair<int, int> solve(trie_node *v, int k) {
    
    pair<int, int>result = make_pair(0, 0);
    vector<int>sons;
    int sum = v -> weight;
    for(int i = 0; i < A; i++) {
        if(v -> children[i] != NULL) {
            pair<int, int>p = solve(v -> children[i], k);
            
            result.second += p.second;
            sons.push_back(p.first);
            sum += p.first;
        }
    }
    
    int t = (int)sons.size() - 1;
    sort(sons.begin(), sons.end());
    
    while(sum > k) {
        sum -= sons[t--];
        result.second++;
    }
    
    if(sum == k) {
        result.second++;
    } else {
        result.first = sum;
    }
    
    return result;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    trie_node *root = new trie_node();
    
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        trie_add(root, s);
    }
    
    pair<int, int>result = solve(root, k);
    
    if(result.first != 0)
        result.second++;
    
    cout << result.second << '\n';
    
    return 0;
}
