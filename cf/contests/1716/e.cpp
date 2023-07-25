#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const long long mod = 998244353;


struct Node {
    long long sum, max_sum, max_prefix, max_suffix;
    Node() : sum(0), max_sum(0), max_prefix(0), max_suffix(0) {}
};

Node merge(Node &a, Node &b) {
    Node answer;
    answer.sum = a.sum + b.sum;
    
    answer.max_sum = max(a.max_sum, b.max_sum);
    answer.max_sum = max(answer.max_sum, a.max_suffix + b.max_prefix);
    
    answer.max_prefix = max(a.max_prefix, a.sum + b.max_prefix);
    answer.max_suffix = max(b.max_suffix, b.sum + a.max_suffix);
    
    return answer;
}

void test_case() {
    int k; scanf("%d", &k);
    int n = 1 << k;
    vector<vector<Node>>nodes(n, vector<Node>(1));
    for(int i = 0; i < n; i++) {
        long long x; scanf("%lld", &x);
        nodes[i][0].max_prefix = max(0ll, x);
        nodes[i][0].max_suffix = max(0ll, x);
        nodes[i][0].max_sum = max(0ll, x);
        nodes[i][0].sum = x;
    }
    for(int len = 2; len <= n; len *= 2) {
        vector<vector<Node>>new_nodes(n / len, vector<Node>(len));
        for(int i = 0; i < (int)nodes.size(); i += 2) {
            for(int k = 0; k < len / 2; k++)
                new_nodes[i / 2][k] = merge(nodes[i][k], nodes[i + 1][k]);
            swap(nodes[i], nodes[i + 1]);
            for(int k = 0; k < len / 2; k++)
                new_nodes[i / 2][k + len / 2] = merge(nodes[i][k], nodes[i + 1][k]);
        }
        swap(nodes, new_nodes);
    }
    
    int current = 0;
    int q; scanf("%d", &q);
    while(q--) {
        int t; scanf("%d", &t);
        current ^= 1 << t;
        printf("%lld\n", nodes[0][current].max_sum);
    }
}

int main() {
    int t = 1;
    while(t--)
        test_case();
}
