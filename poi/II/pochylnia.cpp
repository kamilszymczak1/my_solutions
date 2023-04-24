#include <cstdio>
#include <vector>
#include <cctype>

using namespace std;
int cnt = 0;
int NextInt() {
    int result = 0, c;
    do {
        c = getchar_unlocked();
    } while(!isdigit(c));
    do {
        result = result * 10 + c - '0';
        c = getchar_unlocked();
    } while(isdigit(c));
    return result;
}

void PrintInt(int x) {
    int rev = x, count = 0;
    if(x == 0) {
        putchar_unlocked('0'); putchar_unlocked('\n');
        return;
    }
    for(; rev % 10 == 0; rev /= 10, count++) {}
    rev = 0;
    for(; x != 0; x /= 10)
        rev = (rev << 3) + (rev << 1) + x % 10;
    for(; rev; rev /= 10)
        putchar_unlocked('0' + rev % 10);
    while(count--)
        putchar_unlocked('0');
    putchar_unlocked('\n');
}

vector<int>v;
int n, beg = 0;

void MoveThreeBarrels(int pos) {
    if(pos == n - 3)
        return;
    cnt++;
    for(int j = 0; j < 3; j++) {
        v.push_back(v[pos + j]);
    }
    v.erase(v.begin() + pos, v.begin() + pos + 3);
}

void MoveBarrelsPrefix(int prefixLen) {
    for(int i = 0; i < prefixLen; i += 3) {
        cnt++;
        for(int j = 0; j < 3; j++) {
            v.push_back(v[beg + i + j]);
        }
    }
    v.erase(v.begin() + beg, v.begin() + beg + prefixLen);
}

void MoveToFront(int i) {
    if(i == beg)
        return;
    int x = i - beg;
    int y = n - i - 1;
    if(x % 3 == 0) {
        MoveBarrelsPrefix(x);
        return;
    }
    if(y == 0) {
        MoveThreeBarrels(beg);
        y += 3;
        x -= 3;
        i -= 3;
    }
    if(y == 1) {
        MoveThreeBarrels(beg);
        if(x == 2) {
            MoveThreeBarrels(beg);
            return;
        } else {
            y += 3;
            x -= 3;
            i -= 3;
        }
    }
    
    if(x == 0)
        return;
    
    if((x + y) % 3 == 0) {
        if(x == 1) {
            MoveBarrelsPrefix(x + y);
            MoveThreeBarrels(beg);
            MoveBarrelsPrefix(x + y);
        } else {
            MoveThreeBarrels(i - 2);
            MoveBarrelsPrefix(x + y);
        }
    } else if((x + y + 2) % 3 == 0) {
        MoveThreeBarrels(i - 1);
        MoveBarrelsPrefix(x + y - 1);
    } else {
        MoveThreeBarrels(i);
        MoveBarrelsPrefix(x + y - 2);
    }
}

int main() {
    n = NextInt();
    for(int i = 0; i < n; i++) {
        char c;
        do {
            c = getchar_unlocked();
        } while(c != 'c' && c != 'n' && c != 'z');
        v.push_back(c == 'c' ? 1 : c == 'n' ? 2 : 3);
    }
    
    for(int i = 0; i < n; i++) {
        if(v[i] == 1) {
            MoveToFront(i);
            i = beg;
            beg++;
        }
    }
    
    
    for(int i = 0; i < n; i++) {
        if(v[i] == 2) {
            MoveToFront(i);   
            i = beg;
            beg++;
        }
    }
    PrintInt(cnt);
    return 0;
}
