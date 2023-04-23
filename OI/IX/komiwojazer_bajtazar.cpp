#include <iostream>
#include <vector>
#define MAX_N 40000
#define inf 10000000

using namespace std;

long int leafCount = 1;
long int treeSize = 1;
vector<int>tree;

int n,preorderCounter=0;
vector<int>graph[MAX_N];
int distanceToRoot[MAX_N];
int preorder[MAX_N];
int findNodeByPreorder[MAX_N];
int firstAppearInPath[MAX_N];

void makeTree(vector<int>values);
int minInTree(int a, int b);

void loadGraph();
void distanceDFS(int v);
void prepareForLCA();
void DFSPath(vector<int>&path, int v, int p);
int LCA(int a, int b);
long long getDistance(int a, int b);

int main() {
    ios_base::sync_with_stdio(0);
    
    loadGraph();
    for(int i = 1; i < n; i++) distanceToRoot[i] = -1;
    distanceDFS(0);
    
    prepareForLCA();
    
    int q,a,b;
    cin >> q >> b;
    long long result = getDistance(0, b - 1);
    for(int i = 1; i < q; i++) {
        cin >> a;
        result = result + getDistance(b - 1, a - 1);
        b = a;
    }
    cout << result << "\n";
    return 0;
}

//gets node number from 0 to n-1
long long getDistance(int a, int b) {
    long long result = distanceToRoot[a] + distanceToRoot[b];
    int lca = LCA(a,b);
    result = result - 2 * distanceToRoot[lca];
    return result;
}


//gets node number from 0 to n-1
int LCA(int a,int b) {
    int c,d,lcaPreorder,lca;
    c = preorder[a];
    d = preorder[b];
        
    c = firstAppearInPath[c];
    d = firstAppearInPath[d];
        
    lcaPreorder = minInTree(c,d);
    lca = findNodeByPreorder[lcaPreorder];
    return lca;
}

void prepareForLCA() {
    for(int i = 0; i < n; i++) firstAppearInPath[i] = -1;
    vector<int>path;
    DFSPath(path, 0, -1);
    makeTree(path);
}

void DFSPath(vector<int> &path,int v,int p) {
    path.push_back(preorder[v]);
    firstAppearInPath[preorder[v]] = path.size() - 1;
    for(int v1 : graph[v]) {
        if(v1 != p) {
            DFSPath(path, v1, v);
            path.push_back(preorder[v]);
        }
    }
}

void distanceDFS(int v) {
    preorder[v] = preorderCounter++;
    findNodeByPreorder[preorderCounter - 1] = v;
    for(int v1 : graph[v]) {
        if(distanceToRoot[v1] == -1) {
            distanceToRoot[v1] = distanceToRoot[v] + 1;
            distanceDFS(v1);
        }
    }
}

int minInTree(int a,int b) {
    if(a > b) swap(a, b);
    a += leafCount;
    b += leafCount;
    int res = min(tree[a], tree[b]);
    while(a/2 != b/2) {
        if(a % 2 == 0) res = min(res, tree[a + 1]);
        if(b % 2 != 0) res = min(res, tree[b - 1]);
        a = a / 2;
        b = b / 2;
    }
    return res;
}

void makeTree(vector<int>values) {
    
    while(leafCount < (int)values.size()) leafCount *= 2;
    treeSize = leafCount * 2;
    tree.resize(treeSize);
    
    for(int i=0; i < (int)values.size(); i++) {
        tree[i + leafCount] = values[i];
    }
    for(int i = values.size(); i < leafCount; i++) {
        tree[i + leafCount] = inf;
    }
    for(int i = leafCount - 1; i > 0; i--) {
        tree[i] = min(tree[i * 2 + 1], tree[i * 2]);
    }
}

void loadGraph() {
    int a, b;
    cin >> n;
    for(int i = 1; i < n; i++) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }
}
