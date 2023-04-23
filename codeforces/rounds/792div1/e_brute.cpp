#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
const int N=1e5+2;
int T,n,k,mex,cnt,b[N*2],m;
map<int,int> p;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=0;i<=n;++i) b[i]=0;
        for(int i=1,x;i<=n;++i){
            scanf("%d",&x);
            x>n?++p[x]:++b[x];
        }
        for(mex=cnt=0;cnt<=k&&mex<=n;++mex)
            cnt+=!b[mex];
        --mex,m=n,cnt=0;
        for(auto it=p.begin();p.size();it=p.erase(it))
            b[++m]=it->second;
        sort(b+mex,b+m+1);
        for(int i=mex;i<=m;++i){
            k-=b[i];
            if(k<0) ++cnt;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
