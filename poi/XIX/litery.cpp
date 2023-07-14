#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int leafCount = 1 << 20;
const int R = 26;

int tree[leafCount * 2];

int n;
char c;

queue<int>positions[R];

string ReadData();

void Update(int x, int val);
int GetSum(int a, int b);

int main() {
    ios_base::sync_with_stdio(0);
    
    long long result = 0;
    string s = ReadData();
    
    for(int i = 0; i < n; i++) {
        c = s[i];
        
        int nextPos = positions[c - 'A'].front();
        positions[c - 'A'].pop();
        
        int dist = nextPos + GetSum(0, nextPos);
        
        result += dist;
        Update(nextPos, -1);
    }
    
    cout << result << "\n";
    
    return 0;
}


void Update(int x, int val) {
    x += leafCount;
    while(x) {
        tree[x] += val;
        x >>= 1;
    }
}

int GetSum(int a, int b) {
    a += leafCount;
    b += leafCount;
    int result = tree[a];
    if(a != b)
        result += tree[b];
    
    while(a / 2 != b / 2) {
        if(a % 2 == 0)
            result += tree[a + 1];
        if(b % 2 == 1)
            result += tree[b - 1];
        a >>= 1;
        b >>= 1;
    }
    
    return result;
}


string ReadData() {
    string s, s1;
    cin >> n >> s >> s1;
    for(int i = 0; i < n; i++) {
        c = s[i];
        positions[c - 'A'].push(i);
    }
    return s1;
}
