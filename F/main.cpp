#include <bits/stdc++.h>

#define ll long long
#define x first
#define y second
#define pb push_back
#define sz(u) (int)(u.size())
#define all(u) u.begin(),u.end()
#define INF 1000000000000000000LL

using namespace std;

const int MAXN=1e5+5;
int n,m;
pair<pair<int,int>,ll> v[MAXN];
vector<ll> seg(4*MAXN),lazy(4*MAXN);

void prop(int p, int l, int r)
{
    if(lazy[p]==INF) return;
    if(l==r) seg[p]=min(lazy[p],seg[p]);
    else
    {
        lazy[p*2]=min(lazy[p*2],lazy[p]);
        lazy[p*2+1]=min(lazy[p*2+1],lazy[p]);
    }
    lazy[p]=INF;
}

void update(int a, int b, ll val, int l=0, int r=n, int p=1)
{
    prop(p,l,r);
    if(l>b || r<a) return;
    if(a<=l && r<=b)
    {
        lazy[p]=val;
        prop(p,l,r);
        return;
    }
    int md=(l+r)/2;
    update(a,b,val,l,md,p*2);
    update(a,b,val,md+1,r,p*2+1);
}

ll query(int i, int l=0, int r=n, int p=1)
{
    prop(p,l,r);
    if(l>i || r<i) return INF;
    if(l==r) return seg[p];
    int md=(l+r)/2;
    return min(query(i,l,md,p*2),query(i,md+1,r,p*2+1));
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<m;i++) cin>>v[i].x.x>>v[i].x.y>>v[i].y;
    sort(v,v+m);
    for(int i=0;i<MAXN*4;i++) lazy[i]=seg[i]=INF;
    update(0,0,0);
    for(int i=0;i<m;i++)
    {
        ll l=v[i].x.x, r=v[i].x.y, val=(r-l+1)*v[i].y;
        ll gt=query(l-1);
        if(gt!=INF) update(l,r,gt+val);
    }
    ll ans=query(n);
    cout<<(ans>=INF?-1:ans);
    return 0;
}

