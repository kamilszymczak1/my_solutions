#include <iostream>
using namespace std;
void test_case(){
    int n,a,b; cin >> n >> a >> b;
    if(a > b){
        cout << 1 << "\n";
        return;
    }
    cout << n / a + (n % a > 0) << "\n";
}
int main(){
    ios_base :: sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    while(t--)
        test_case();
}
