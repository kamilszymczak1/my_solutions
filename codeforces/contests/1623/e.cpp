#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void DFS(int x, vector<pair<int, int>>&children, vector<int>&inorder) {
    if(children[x].first != -1)
        DFS(children[x].first, children, inorder);
    inorder.push_back(x);
    if(children[x].second != -1)
        DFS(children[x].second, children, inorder);
}

bool Get(int x, vector<pair<int, int>>&children, vector<bool>&needsDuplicating, vector<bool>&duplicated, int &k, int cost) {
    bool duplicatedChild = false;
    if(children[x].first != -1)
        duplicatedChild |= Get(children[x].first, children, needsDuplicating, duplicated, k, cost + 1);
    if(duplicatedChild || (needsDuplicating[x] && cost <= k)) {
        if(!duplicatedChild)
            k -= cost;
        duplicated[x] = true;
    }
    if(children[x].second != -1 && duplicated[x])
        Get(children[x].second, children, needsDuplicating, duplicated, k, 1);
    return duplicated[x];
}

void TestCase() {
    int n, k; cin >> n >> k;
    string label; cin >> label;
    vector<pair<int, int>>children(n);
    for(int i = 0; i < n; i++) {
        cin >> children[i].first >> children[i].second;
        children[i].first--; children[i].second--;
    }
    vector<int>inorder;
    DFS(0, children, inorder);
    vector<bool>needsDuplicating(n), duplicated(n, false);
    char last = label[inorder.back()];
    for(int i = n - 2; i >= 0; i--) {
        int x = inorder[i];
        if(label[inorder[i + 1]] != label[x])
            last = label[inorder[i + 1]];
        if(label[x] < last)
            needsDuplicating[x] = true;
    }
    vector<int>nonDuplicatedAncestors;
    Get(0, children, needsDuplicating, duplicated, k, 1);
    for(int x : inorder) {
        cout << label[x];
        if(duplicated[x])
            cout << label[x];
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
