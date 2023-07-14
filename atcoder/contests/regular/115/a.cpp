#include<iostream>

using namespace std;

typedef long long int lli;

#include<bits/stdc++.h>
#define M 1000000007
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<stdio.h>
struct node
{
    lli product;
    lli plush;
    lli reinit;
} pending[1000000];
lli seg[1000000];
lli arr[1000000];
lli ul,uu;
lli qu,ql;
int type;
lli val;
void update(lli index,lli begin,lli end) {
    if(pending[index].reinit!=0 || pending[index].plush!=0 || pending[index].product!=1) {
        int flag=0;
        if(pending[index].reinit!=0) {
            flag=1;
            seg[index]=((end-begin+1)*pending[index].reinit)%M;
            if(begin!=end) {
                pending[2*index].reinit=pending[index].reinit;
                pending[2*index+1].reinit=pending[index].reinit;
                pending[2*index].plush=pending[index].plush;//((pending[index].product*pending[2*index].plush)%M+pending[index].plush)%M;
                pending[2*index+1].plush=pending[index].plush;//((pending[index].product*pending[2*index+1].plush)%M+pending[index].plush)%M;
                pending[2*index].product=pending[index].product;//(pending[index].product * pending[2*index].product)%M;
                pending[2*index+1].product=pending[index].product;//(pending[2*index+1].product*pending[index].product)%M
            }
        }
        seg[index]=((seg[index]*pending[index].product)%M+(pending[index].plush*(end-begin+1))%M)%M;
        if(begin!=end && flag==0) {
            // pending[2*index].reinit=pending[index].reinit;
            //pending[2*index+1].reinit=pending[index].reinit;
            pending[2*index].plush=((pending[index].product*pending[2*index].plush)%M+pending[index].plush)%M;
            pending[2*index+1].plush=((pending[index].product*pending[2*index+1].plush)%M+pending[index].plush)%M;
            pending[2*index].product=(pending[index].product*pending[2*index].product)%M;
            pending[2*index+1].product=(pending[2*index+1].product*pending[index].product)%M;
        }
        pending[index].product=1;
        pending[index].plush=0;
        pending[index].reinit=0;
    }
    if(begin>end ||  ul>end || uu<begin) return;
    else if(begin>=ul && end<=uu) {
        if(type==1) {
            seg[index]=(seg[index]+(end-begin+1)*val)%M;
            if(end!=begin) {
                pending[2*index].plush=(pending[2*index].plush+val)%M;
                pending[2*index+1].plush= (pending[2*index+1].plush+val)%M;
            }
        } else if(type==2) {
            seg[index]=(seg[index]*val)%M;
            if(begin!=end) {
                pending[2*index].product=(pending[2*index].product*val)%M;
                pending[2*index+1].product=(pending[2*index+1].product*val)%M;
                pending[2*index].plush=(pending[2*index].plush*val)%M;
                pending[2*index+1].plush=(pending[2*index+1].plush*val)%M;
            }
        }
        if(type==3) {
            seg[index]=(val*(end-begin+1))%M;
            if(begin!=end) {
                pending[2*index].reinit=val;
                pending[2*index+1].reinit=val;
                pending[2*index].plush=0;
                pending[2*index+1].plush=0;
                pending[2*index].product=1;
                pending[2*index+1].product=1;
            }
        }
        return;
    }
    update(2*index,begin,(begin+end)/2);
    update(2*index+1,(begin+end)/2+1,end);
    seg[index]= (seg[2*index]+seg[2*index+1])%M;
}
lli build(int index,int begin,int end) {
    if(begin==end) {
        seg[index]=arr[begin];
        return seg[index];
    }
    if(begin>end) return 0;
    build(2*index,begin,(begin+end)/2);
    build(2*index+1,(begin+end)/2+1,end);
    seg[index]=(seg[2*index+1]+seg[2*index])%M;
}
lli query(int index,int begin,int end) {
    if(pending[index].reinit!=0 || pending[index].plush!=0 || pending[index].product!=1) {
        int flag=0;
        if(pending[index].reinit!=0) {
            flag=1;
            seg[index]=((end-begin+1)*pending[index].reinit)%M;
            if(begin!=end) {
                pending[2*index].reinit=pending[index].reinit;
                pending[2*index+1].reinit=pending[index].reinit;
                pending[2*index].plush=pending[index].plush;//((pending[index].product*pending[2*index].plush)%M+pending[index].plush)%M;
                pending[2*index+1].plush=pending[index].plush;//((pending[index].product*pending[2*index+1].plush)%M+pending[index].plush)%M;
                pending[2*index].product=pending[index].product;//(pending[index].product * pending[2*index].product)%M;
                pending[2*index+1].product=pending[index].product;//(pending[2*index+1].product*pending[index].product)%M
            }
        }
        seg[index]=((seg[index]*pending[index].product)%M+(pending[index].plush*(end-begin+1))%M)%M;
        if(begin!=end && flag==0) {
            //pending[2*index].reinit=pending[index].reinit;
            //pending[2*index+1].reinit=pending[index].reinit;
            pending[2*index].plush=((pending[index].product*pending[2*index].plush)%M+pending[index].plush)%M;
            pending[2*index+1].plush=((pending[index].product*pending[2*index+1].plush)%M+pending[index].plush)%M;
            pending[2*index].product=(pending[index].product*pending[2*index].product)%M;
            pending[2*index+1].product=(pending[2*index+1].product*pending[index].product)%M;
        }
        pending[index].product=1;
        pending[index].plush=0;
        pending[index].reinit=0;
    }
    if(begin>end || begin>qu || end<ql) return 0;
    if(begin>=ql && end<=qu) {
        return seg[index];
    }
    lli a=query(2*index,begin,(begin+end)/2);
    lli b=query(2*index+1,(begin+end)/2+1,end);
    return (a+b)%M;
}

int main() {
    int t;
    lli n,m;
    scanf("%lld %lld ",&n,&m);
    for(int i=0;i<n;i++) {
        scanf("%lld",&arr[i]);
    }
    build(1,0,n-1);
    //  cout<<" build seg array "<<endl
    // for(int i=0;i<10;i++) cout<<seg[i]<<" ";
        //cout<<endl;
    for(int i=0;i<4*n+100;i++) {
        pending[i].product=1;
        pending[i].plush=0;
        pending[i].reinit=0;
    }
    for(int i=0;i<m;i++) {
    // lli type;
        scanf("%d",&type);
        //cout<<" type "<<type<<endl;
        if(type==1) {
        //	 cout<<"type1"<<endl;
            scanf("%lld %lld %lld",&ul,&uu,&val);
            ul-=1;
            uu-=1;
            update(1,0,n-1);
        }
        if(type==2) {
            //	cout<<"type2"<<endl;
            scanf("%lld %lld %lld",&ul,&uu,&val);
            ul-=1;
            uu-=1;
            update(1,0,n-1);
        }
        if(type==3) {
        //	cout<<"type3"<<endl;
            scanf("%lld %lld %lld",&ul,&uu,&val);
            ul-=1;
            uu-=1;
            update(1,0,n-1);
        }
        if(type==4) {
        //cout<<"type4"<<endl;
            scanf("%lld %lld",&ql,&qu);
            ql-=1;
            qu-=1;
            lli ans=query(1,0,n-1);
            cout<<ans<<endl;
        }
    }
    return 0;

}
