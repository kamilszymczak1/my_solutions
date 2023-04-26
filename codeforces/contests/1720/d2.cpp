#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Trie {
    struct Node {
        Node *children[2];
        int b[4];
        Node() {
            children[0] = children[1] = NULL;
            for(int i = 0; i < 4; i++) {
                b[i] = 0;
            }
        }
    };
    
    Node *root;
    const int depth = 30;
    int mapped_id[4] = { 0b10, 0b00, 0b11, 0b01 };
    Trie() {
        root = new Node();
    }
    
    
    void insert(int ind, int val, int dp_val) {
        int x = ind ^ val;
        Node *current = root;
        for(int i = depth - 1; i >= 0; i--) {
            int k = (x >> i) & 1;
            
            int t = ((ind >> i) & 1) * 2 + ((val >> i) & 1);
            current -> b[t] = max(current -> b[t], dp_val);
            
            if(current -> children[k] == NULL)
                current -> children[k] = new Node();
            
            current = current -> children[k];
            
            
            
            
        }
    }
    
    int get_max(int ind, int val) {
        int x = ind ^ val;
        int result = 0;
        Node *current = root;
        for(int i = depth - 1; i >= 0; i--) {
            
            int k = (x >> i) & 1;
            
            int t = ((ind >> i) & 1) * 2 + ((val >> i) & 1);
            result = max(result, current -> b[mapped_id[t]]);
            
            
            if(current -> children[k] == NULL)
                current -> children[k] = new Node();
            
            current = current -> children[k];
            
            
            
            
        }
        return result;
    }
};

void test_case() {
    int n; scanf("%d", &n);
    Trie T;
    
    int result = 0;
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        int dp = T.get_max(i, a);
        result = max(result, dp + 1);
        T.insert(i, a, dp + 1);
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
