

#include <iostream>

#define MAX_N 10000

using namespace std;

const int leafCount = 16384;
int tree[leafCount * 2];

bool Generate(int sum, int length);
void Add(int a, int b, int val);
int GetVal(int x);
void Sum(int i, int sum);

int main() {
    ios_base::sync_with_stdio(0);
    
    bool negative = false;
    int n, s;
    cin >> n >> s;
    
    if(s < 0)
        negative = true;
    s = abs(s);
    
    
    if(Generate(s, n)) {
        
        Sum(1, 0);
        
        int mult = negative ? -1 : 1;
        for(int i = 0; i < n; i++)
            cout << mult * tree[i + leafCount] << " ";
        cout << "\n";
    } else
        cout << "NIE\n";
    
    return 0;
}

bool Generate(int sum, int length) {
    if(length * (length - 1) / 2 < sum || sum % 2 != (length / 2) % 2)
        return false;
    
    tree[leafCount + 0] = 0;
    tree[leafCount + 1] = 1;
    for(int i = 2; i < length; i++) {
        if(tree[i - 1 + leafCount] == 1 || tree[i - 1 + leafCount] == -1)
            tree[i + leafCount] = 0;
        else
            tree[i + leafCount] = tree[i - 2 + leafCount] == 1 ? -1 : 1;
    }
    
    int current = sum % 2;
    
    int i = length - 1;
    
    while(current < sum) {
        while(GetVal(i) != GetVal(i - 1) - 1)
            i--;
        if(current + (length - i) * 2 <= sum) {
            current += (length - i) * 2;
            Add(i, length - 1, 2);
        } else {
            int j = i;
            while(current < sum) {
                j++;
                current += 2;
            }
            Add(i, j - 1, 2);
        }
    }
    return true;
}

int GetVal(int x) {
    x += leafCount;
    int result = 0;
    while(x != 0) {
        result += tree[x];
        x >>= 1;
    }
    return result;
}

void Add(int a, int b, int val) {
    a += leafCount;
    b += leafCount;
    
    tree[a] += val;
    if(a != b)
        tree[b] += val;
    
    while(a / 2 != b / 2) {
        if(a % 2 == 0)
            tree[a + 1] += val;
        if(b % 2 == 1)
            tree[b - 1] += val;
        
        a >>= 1;
        b >>= 1;
    }
}

void Sum(int i, int sum) {
    tree[i] += sum;
    sum = tree[i];
    if(i < leafCount) {
        Sum(i * 2, sum);
        Sum(i * 2 + 1, sum);
    }
}

