#include <bits/stdc++.h>
using namespace std;
struct Z{
    int n, L;
    vector<int> f;
    Z(int _n,int _L):n(_n),L(_L),f(4*_n,_L){}
    void upd(int o,int l,int r,int p,int v){
        if(l==r){f[o]=v;return;}
        int m=(l+r)>>1;
        if(p<=m) upd(o<<1,l,m,p,v);
        else     upd(o<<1|1,m+1,r,p,v);
        f[o]=max(f[o<<1],f[o<<1|1]);
    }
    int qry(int o,int l,int r,int R){
        if(f[o]<=R) return -1;
        if(l==r) return l;
        int m=(l+r)>>1;
        int t=qry(o<<1,l,m,R);
        return t!=-1? t: qry(o<<1|1,m+1,r,R);
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,q;
    cin>>n>>q;
    vector<int> v(n+1);
    int mv=0;
    for(int i=1;i<=n;i++){
        cin>>v[i];
        mv=max(mv,v[i]);
    }
    int S=mv+2, INF=n+1;
    vector<vector<pair<int,int>>> qs(n+2);
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        qs[l].emplace_back(r,i);
    }
    vector<int> res(q);
    Z T(S,INF);
    for(int i=n;i>=1;i--){
        T.upd(1,0,S-1,v[i],i);
        for(auto &pr:qs[i]) res[pr.second]=T.qry(1,0,S-1,pr.first);
    }
    for(int i=0;i<q;i++) cout<<res[i]<<endl;
    return 0;
}
