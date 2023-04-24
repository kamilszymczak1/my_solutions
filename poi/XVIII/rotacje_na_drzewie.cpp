#include <iostream>
#include <set>

using namespace std;

constexpr int leafCount = 1 << 18;
int tree[leafCount << 1], n;

void Add(int i, int value) {
    tree[i += leafCount] += value;
    for(i >>= 1; i; i >>= 1)
        tree[i] += value;
}

int PrefixSum(int i) {
    if(i < 0)
        return 0;
    int result = tree[i += leafCount];
    for(; i; i >>= 1)
        result += i & 1 ? tree[i - 1] : 0;
    return result;
}

struct Node {
    int label, subtreeLeaves;
    set<int>subtreeLabels;
    Node *left, *right;
    Node() : left(NULL), right(NULL), label(-1) {}
} *root;

void LoadTree(Node *v) {
    int x; cin >> x;
    if(x == 0) {
        v -> left = new Node();
        v -> right = new Node();
        LoadTree(v -> left);
        LoadTree(v -> right);
    } else {
        v -> subtreeLabels.insert(x - 1);
        v -> label = x - 1;
    }
}

void DFS(Node *v) {
    if(v -> label >= 0) {
        v -> subtreeLeaves = 1;
    } else {
        DFS(v -> left);
        DFS(v -> right);
        v -> subtreeLeaves = v -> right -> subtreeLeaves + v -> left -> subtreeLeaves;
        if(v -> right -> subtreeLeaves > v -> left -> subtreeLeaves)
            swap(v -> right, v -> left);
    }
    
}

long long Solve(Node *v) {
    if(v -> label >= 0) {
        Add(v -> label, 1);
        return 0;
    }
    long long result = Solve(v -> right);
    for(int x : v -> right -> subtreeLabels)
        Add(x, -1);
    result += Solve(v -> left);
    swap(v -> subtreeLabels, v -> left -> subtreeLabels);
    long long inversions = 0;
    for(int x : v -> right -> subtreeLabels)
        inversions += PrefixSum(x - 1);
    for(int x : v -> right -> subtreeLabels) {
        Add(x, 1);
        v -> subtreeLabels.insert(x);
    }  
    v -> right -> subtreeLabels.clear();
    long long a = v -> left -> subtreeLeaves;
    long long b = v -> right -> subtreeLeaves;
    return result + min(inversions, a * b - inversions);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    root = new Node();
    LoadTree(root);
    DFS(root);
    cout << Solve(root) << '\n';
    return 0;
}
