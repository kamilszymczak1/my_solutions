#include <iostream>

using namespace std;

enum Color {
    BLACK, WHITE, RED, NONE
};

struct Node {
    Node *left, *right, *parent;
    Color color;
    Node(Node *p) {
        parent = p;
        left = right = NULL;
        color = NONE;
    }
};

Node *root;
int resultMax = 0, resultMin = 0;

int MakeTree(Node *n, int pos, string &s);
void DFSMax(Node *n);
void DFSMin(Node *n);

int main() {
    ios_base::sync_with_stdio(0);
    
    root = new Node(NULL);
    
    string s;
    int p = 0;
    cin >> s;
    MakeTree(root, p, s);
   
    DFSMax(root);
    DFSMin(root);
    
    cout << resultMax << " " << resultMin << "\n";
    
    return 0;
}

Node* leftBrother(Node *n) {
    if(n -> parent == NULL)
        return NULL;
    return (n -> parent -> left);
}

void DFSMax(Node *n) {
    if(n -> left != NULL)
        DFSMax(n -> left);
    if(n -> right != NULL)
        DFSMax(n -> right);
    
    Node *bro = leftBrother(n);
    
    Color left = NONE, right = NONE, brother = NONE;
    if(n -> right != NULL)
        right = n -> right -> color;
    if(n -> left != NULL)
        left = n -> left -> color;
    if(bro != NULL)
        brother = bro -> color;
    
    if(left != RED && right != RED && brother != RED)
        n -> color = RED, resultMax++;
    else
        n -> color = WHITE;
}

void DFSMin(Node *n) {
    if(n -> left != NULL)
        DFSMin(n -> left);
    if(n -> right != NULL)
        DFSMin(n -> right);
    
    Color left = NONE, right = NONE, brother = NONE;
    
    Node *bro = leftBrother(n);
    
    if(n -> left != NULL)
        left = n -> left -> color;
    if(n -> right != NULL)
        right = n -> right -> color;
    if(bro != NULL)
        brother = bro -> color;
    
    if(left != NONE && left != RED && right != NONE && right != RED)
        n -> color = RED, resultMin++;
    else
        n -> color = WHITE;
}

void ClearColor(Node *n) {
    if(n -> left != NULL)
        ClearColor(n -> left);
    if(n -> right != NULL)
        ClearColor(n -> right);
    n -> color = NONE;
}

int MakeTree(Node* n, int pos, string &s) {
    if(s[pos] == '0')
        return pos + 1;
    if(s[pos] == '1') {
        pos++;
        n -> left = new Node(n);
        return MakeTree(n -> left, pos, s);
    } else {
        n -> left = new Node(n);
        n -> right = new Node(n);
        pos++;
        int p = MakeTree(n -> left, pos, s);
        return MakeTree(n -> right, p, s);
    }
}
