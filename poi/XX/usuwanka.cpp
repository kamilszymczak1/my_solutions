#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Brick {
    int pos;
    int val;
    Brick(int p, int v) {
        pos = p;
        val = v;
    }
};

stack<vector<int>>result;
vector<Brick>mainStack, secondStack;

int n, k;

void ReadData();

void Solve();

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    Solve();
    
    while(!result.empty()) {
        for(int x : result.top())
            cout << x << " ";
        cout << "\n";
        result.pop();
    }
    
    return 0;
}

void Solve() {
    int secondTopSum = 0;
    while(!mainStack.empty()) {
        
        while(secondStack.size() <= k) {
            secondStack.push_back(mainStack.back());
            secondTopSum += secondStack.back().val;
            mainStack.pop_back();
        }
        
        if(secondTopSum == 0) {
            
            result.push(vector<int>());
            for(int i = 0; i < k + 1; i++) {
                result.top().push_back(secondStack.back().pos);
                secondStack.pop_back();
            }
            secondTopSum = 0;
            for(int i = 1; i < k + 2; i++)
                if(i > secondStack.size())
                    break;
                else
                    secondTopSum += secondStack[secondStack.size() - i].val;
            
        } else {
            secondTopSum -= secondStack[secondStack.size() - k - 1].val;
            secondTopSum += mainStack.back().val;
            secondStack.push_back(mainStack.back());
            mainStack.pop_back();
        }
    }
}

void ReadData() {
    string s;
    cin >> n >> k >> s;
    for(int i = 0; i < n; i++) {
        int val = s[i] == 'c' ? -k : 1;
        mainStack.push_back(Brick(i + 1, val));
    }
}
