#include <iostream>
#include <stack>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n, a, result = 0;
    
    stack<int>s;
    s.push(0);
    
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> a >> a;
        
        if(a > s.top())
            s.push(a);
        
        if(a < s.top()) {
            
            while(s.top() > a)
                s.pop(), result++;
            
            if(s.top() != a) 
                s.push(a);
            
        }
    }
    
    result += s.size() - 1;
    
    cout << result << "\n";
    
    return 0;
}
