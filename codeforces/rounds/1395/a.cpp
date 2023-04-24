#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int colours[4], t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        for(int j = 0; j < 4; j++)
            cin >> colours[j];
        
        int notEvenCount = 0;
        for(int j = 0; j < 4; j++)
            if(colours[j] % 2 != 0)
                notEvenCount++;
            
            bool result = true;
        
        if(notEvenCount <= 1) {
            result = true;
        } else {
            notEvenCount = 0;
            for(int i = 0; i < 3; i++) {
                if(colours[i] == 0) {
                    result = false;
                    break;
                }
                colours[i]--;
                if(colours[i] % 2 != 0)
                    notEvenCount++;
            }
            if(colours[3] % 2 == 0)
                notEvenCount++;
            if(result)
                result = notEvenCount <= 1;
        }
        
        if(result)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    
    return 0;
}
