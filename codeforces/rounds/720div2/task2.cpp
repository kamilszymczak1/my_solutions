#include <stdio.h>
#include <algorithm>
#include <cctype>
#include <deque>
#include <iostream>

using namespace std;

int NextInt() {
    int result = 0, c;
    do {
        c = getchar();
    } while(!isdigit(c));
    do {
        result = (result << 3) + (result << 1) + c - '0';
        c = getchar();
    } while(isdigit(c));
    return result;
}
void WriteInt(long long x) {
    if(x == 0) {
        putchar('0');
    } else {
        long long rev = x, zeroes = 0;
        for(; rev % 10 == 0; rev /= 10, zeroes++) {}
        for(rev = 0; x; x /= 10)
            rev = (rev << 3) + (rev << 1) + x % 10;
        for(; rev; rev /= 10)
            putchar(rev % 10 + '0');
        while(zeroes--)
            putchar('0');
    }
    putchar(' ');
}



const int MAX_N = 100007;
int v[MAX_N];
int ans[MAX_N][4];
bool used[MAX_N];
pair<int, int>p[MAX_N];

void TestCase() {
    int n = NextInt();
    for(int i = 0; i < n; i++) {
        v[i] = NextInt();
        p[i] = make_pair(v[i], i);
        used[i] = false;
    }
    WriteInt(n);
    putchar('\n');
    for(int i = 0; i < n; i++) {
        
        WriteInt(v[i]);
    }
    putchar('\n');
    sort(p, p + n);
    deque<int>q;
    int x = 0;
    
    set<int>cmp
    
    for(int i = 0; i < n; i++) {
        if(used[p[i].second]) {
            continue;
        }
        int ind = p[i].second;
        while(!q.empty() && used[q.front()])
            q.pop_front();
        if(!q.empty() && v[q.front()] < v[ind]) {
            ind = q.front();
            q.pop_front();
            i--;
        }
        
        used[ind] = true;
        if(ind != 0 && !used[ind - 1]) {
            ans[x][0] = ind;
            ans[x][1] = ind + 1;
            ans[x][2] = v[ind] + 1;
            ans[x++][3] = v[ind];
            v[ind - 1] = v[ind] + 1;
            q.push_back(ind - 1);
        }
        
        if(ind != n - 1 && !used[ind + 1]) {
            ans[x][0] = ind + 2;
            ans[x][1] = ind + 1;
            ans[x][2] = v[ind] + 1;
            ans[x++][3] = v[ind];
            v[ind + 1] = v[ind] + 1;
            q.push_back(ind + 1);
        }
       
       cout << "V = ";
        for(int j = 0; j < n; j++)
            cout << v[j] << ' ';
        cout << '\n';
    }
    WriteInt(x);
    putchar('\n');
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < 4; j++)
            WriteInt(ans[i][j]);
        putchar('\n');
    }
}

int main() {
    int t = NextInt();
    while(t--)
        TestCase();
    return 0;
}
