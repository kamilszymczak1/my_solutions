#include <cstdio>
#include <cctype>
#include <vector>

using namespace std;
constexpr int MAX_N = 2007;
int n, arr[MAX_N];
vector<pair<int, char>>ans;

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
    int reversed = x, zeroes = 0;
    if(x == 0) {
        putchar('0');
        return;
    }
    for(; reversed % 10 == 0; reversed /= 10, zeroes++) {}
    reversed = 0;
    for(; x; x /= 10) {
        reversed = reversed * 10 + x % 10;
    }
    for(; reversed; reversed /= 10) {
        putchar(reversed % 10 + '0');
    }
    while(zeroes--)
        putchar('0');
}

void AddMoves(int amount, char type) {
    if(!ans.empty() && ans.back().second == type) {
        ans.back().first += amount;
    } else {
        ans.emplace_back(amount, type);
    }
    ans.back().first %= type == 'b' ? 3 : n;
    if(ans.back().first == 0)
        ans.pop_back();
}

void PerformB(int i) {
    swap(arr[i], arr[i - 1]); swap(arr[i - 1], arr[i - 2]);
}

bool Sort() {
    if(n <= 3) {
        int count = 0;
        if(n == 2 && arr[0] > arr[1])
            AddMoves(1, 'a');
        if(n == 3) {
            int count = 0;
            while(arr[0] != 1 || arr[1] != 2 || arr[2] != 3) {
                AddMoves(1, 'a'); swap(arr[1], arr[2]); swap(arr[0], arr[1]);
                if(count++ > 3)
                    return false;
            }
        }
        return count <= 2;
    }
    
    int pos = 0;
    for(int i = 1; i <= n - 2; i++) {
        //find the element with value i and move it to an index i - 1
        for(pos = 0; arr[pos] != i; pos++) {}
        for(; pos > i - 1; pos -= 2) {
            if(pos - i > 0) {
                AddMoves(n - pos + 2, 'a');
                AddMoves(1, 'b');
                AddMoves(pos - 2, 'a');
                PerformB(pos);
            } else {
                AddMoves(n - pos + 1, 'a');
                AddMoves(2, 'b');
                AddMoves(pos - 1, 'a');
                PerformB(pos + 1);
                PerformB(pos + 1);
            }
        }
    }
    
    if(arr[n - 2] < arr[n - 1])
        return true;
    if(n & 1)
        return false;
    
    AddMoves(1, 'a');
    AddMoves(2, 'b');
    for(int i = 0; i * 2 < (n - 4); i++) {
        AddMoves(n - 2, 'a');
        AddMoves(2, 'b');
    }
    AddMoves(n - 4, 'a');
    
    return true;
}

int main() {
    n = NextInt();
    for(int i = 0; i < n; i++)
        arr[i] = NextInt();
    if(Sort()) {
        PrintInt(ans.size());
        putchar_unlocked('\n');
        for(auto [a, b] : ans) {
            PrintInt(a);
            putchar_unlocked(b);
            putchar_unlocked(' ');
        }
        putchar_unlocked('\n');
    } else {
        printf("NIE DA SIE\n");
    }
    
    return 0;
}
