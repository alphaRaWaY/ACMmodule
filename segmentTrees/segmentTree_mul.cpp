// https://www.luogu.com.cn/problem/P3373
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)
int ls(int i)
{
    return (i<<1);
}
int rs(int i)
{
    return (i<<1)|1;
}
const int MaxN(1e6+5);
int n,q,mod;
int nums[MaxN];

struct node
{
    int val,l,r;
    int tag,mTag;
    int length()
    {
        return r-l+1;
    }
}tree[MaxN];
void buildtree(int index,int l,int r)
{
    tree[index].tag=0;
    tree[index].mTag=1;
    tree[index].l=l;
    tree[index].r=r;
    if(tree[index].l==tree[index].r)
    {
        tree[index].val=nums[l]%mod;
        return;
    }
    int mid(((r-l)>>1)+l);
    buildtree(ls(index),l,mid);
    buildtree(rs(index),mid+1,r);
    tree[index].val=(tree[ls(index)].val+tree[rs(index)].val)%mod;
}
void pd(int index)
{
    tree[ls(index)].mTag=(tree[ls(index)].mTag*tree[index].mTag)%mod;
    tree[rs(index)].mTag=(tree[rs(index)].mTag*tree[index].mTag)%mod;
    tree[ls(index)].tag=(tree[ls(index)].tag*tree[index].mTag%mod+tree[index].tag)%mod;
    tree[rs(index)].tag=(tree[rs(index)].tag*tree[index].mTag%mod+tree[index].tag)%mod;
    tree[ls(index)].val=(tree[ls(index)].val*tree[index].mTag%mod+tree[ls(index)].length()*tree[index].tag%mod)%mod;
    tree[rs(index)].val=(tree[rs(index)].val*tree[index].mTag%mod+tree[rs(index)].length()*tree[index].tag%mod)%mod;
    tree[index].tag=0;
    tree[index].mTag=1;
}
int searchTree(int index,int l,int r)
{
    if(tree[index].l>=l&&tree[index].r<=r)return tree[index].val%mod;
    if(tree[index].r<l||tree[index].l>r)return 0;
    pd(index);
    return (searchTree(ls(index),l,r)+searchTree(rs(index),l,r))%mod;
}
void add(int index,int l,int r,int val)
{
    if(tree[index].r<l||tree[index].l>r)return;
    if(tree[index].l>=l&&tree[index].r<=r)
    {
        tree[index].tag=(tree[index].tag+val)%mod;
        tree[index].val=(tree[index].val+val*tree[index].length()%mod)%mod;
        return;
    }
    pd(index);
    add(ls(index),l,r,val);
    add(rs(index),l,r,val);
    tree[index].val=(tree[ls(index)].val+tree[rs(index)].val)%mod;
}
void mul(int index,int l,int r,int val)
{
    if(tree[index].r<l||tree[index].l>r)return;
    if(tree[index].l>=l&&tree[index].r<=r)
    {
        tree[index].mTag=(tree[index].mTag*val)%mod;
        tree[index].tag=tree[index].tag*val%mod;
        tree[index].val=(tree[index].val*val)%mod;
        return;
    }
    pd(index);
    mul(ls(index),l,r,val);
    mul(rs(index),l,r,val);
    tree[index].val=(tree[ls(index)].val+tree[rs(index)].val)%mod;    
}
void dfs(int index)
{
    cout<<tree[index].l<<"-"<<tree[index].r<<" val: "<<tree[index].val%mod<<" ,tag: "<<tree[index].tag<<" ,mTag: "<<tree[index].mTag<<endl;
    if(tree[index].l==tree[index].r)return;
    dfs(ls(index));
    dfs(rs(index));
}
void solve()
{
    cin>>n>>q>>mod;
    inc(i,1,n)
    {
        cin>>nums[i];
    }
    buildtree(1,1,n);
    while(q--)
    {
        int type;
        int a,b,val;
        cin>>type;
        switch (type)
        {
        case 0:
            dfs(1);
            break;
        case 1://*
            cin>>a>>b>>val;
            mul(1,a,b,val);
            break;
        case 2://+
            cin>>a>>b>>val;
            add(1,a,b,val);
            break;
        case 3://search
            cin>>a>>b;
            cout<<searchTree(1,a,b)%mod<<endl;
            break;
        default:
            cout<<"please enter the true type!"<<endl;
            break;
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    int _;
    _=1;
    while(_--)solve();
}