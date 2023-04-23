#include <bits/stdc++.h>

using namespace std;

#define endl '\n'
#define st first
#define nd second
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define ll long long
#define ld long double
ll mod=1000000007;
int inf=1000000007;
ll infl=1000000000000000007;

vector<int>V[10];

int main()
{
    ios_base::sync_with_stdio(0);
//     cin.tie(0);
//     cout.tie(0);
    int tt;
    cin>>tt;
    while(tt--)
    {
        string x;
        cin>>x;
        for(int i=0;i<10;i++) V[i].clear();
        int n=sz(x),k;
        cin>>k;
        x='#'+x;
        for(int i=1;i<=n;i++) V[x[i]-'0'].pb(i);
        for(int i=0;i<10;i++) reverse(all(V[i]));
        int l=0;
        for(int j=0;j<n-k;j++)
        {
            for(int i=0;i<10;i++)
            {
                while(sz(V[i])>0&&V[i].back()<=l) V[i].pop_back();
            }
            for(int i=(j==0);i<10;i++)
            {
                if(sz(V[i])>0&&V[i].back()-l-1<=k)
                {
                    k-=V[i].back()-l-1;
                    l=V[i].back();
                    cout<<i;
                    break;
                }
            }
        }
        cout<<endl;
    }

    return 0;
}
