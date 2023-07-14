#include <iostream>

using namespace std;

struct Node {
    Node *left, *right;
    Node *parent;
    int number;
    Node() {}
    Node(Node *p, int n) {
        parent = p;
        left = NULL;
        right = NULL;
        number = n;
    }
};

int n, counter = 0;

Node *root;

bool LoadTree();
bool IsFullBinary(Node *n);
void InOrderSearch(Node *n);

void Genealogic(Node *n);
void Parenthesis(Node *n);

int main() {
    ios_base::sync_with_stdio(0);
    
    root = new Node(NULL, 1);
    
    if(LoadTree()) {
        Genealogic(root);
        cout << "\n";
        Parenthesis(root);
        cout << "\n";
    } else
        cout << "NIE\n";
    
    return 0;
}

bool LoadTree() {
    cin >> n;
    int val, currentLayer = 0, counter = 1;
    Node *currentNode = root;
    
    for(int i = 0; i < n; i++) {
        cin >> val;
        while(currentLayer < val) {
            if(currentNode -> left != NULL)
                return false;
            
            currentNode -> left = new Node(currentNode, ++counter);
                        
            currentNode = currentNode -> left;
            currentLayer++;
        }
        
        if(currentNode -> parent != NULL)
            currentNode = currentNode -> parent;
        
        while(currentNode -> parent != NULL && currentNode -> right != NULL) {
            currentNode = currentNode -> parent;
            currentLayer--;
        }
        
        
        if(i != n - 1) {
            if(currentNode -> right != NULL)
                return false;
            currentNode -> right = new Node(currentNode, ++counter);
            currentNode = currentNode -> right;
        }
    }
    return IsFullBinary(root);
}

bool IsFullBinary(Node *n) {
    if(n -> left == NULL && n -> right == NULL)
        return true;
    if(n -> left == NULL || n -> right == NULL)
        return false;
    if(!IsFullBinary(n -> left) || !IsFullBinary(n -> right))
        return false;
    return true;
}

void Genealogic(Node *n) {
    if(n -> parent == NULL)
        cout << "0 ";
    else
        cout << n -> parent -> number << " ";
    if(n -> left != NULL)
        Genealogic(n -> left);
    if(n -> right != NULL)
        Genealogic(n -> right);
}

void Parenthesis(Node *n) {
    cout << '(';
    if(n -> left != NULL)
        Parenthesis(n -> left);
    if(n -> right != NULL)
        Parenthesis(n -> right);
    cout << ')';
}
