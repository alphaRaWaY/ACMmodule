#include<bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)

// #define LOCAL
#ifdef LOCAL
#define debug0(x) cout<<"[DEBUG] "<<#x<<"="<<x<<endl
#define debug1(c,l,r) cout<<"[DEBUG] "<<#c<<" : ";\
inc(i,l,r)cout<<c[i]<<" ";cout<<endl
#define debug2(c,l,r,ll,rr)cout<<"[DEBUG]"<<#c<<endl;\
inc(i,l,ll){inc(j,r,rr)cout<<c[i][j]<<" ";cout<<endl;}
ostream& operator<< (ostream& o,const pair<int,int>& a)
{
    o<<"{"<<a.first<<","<<a.second<<"}";
    return o;
}
#else
#define debug0(x)
#define debug1(c,l,r)
#define debug2(c,l,r,ll,rr)
#endif

const int MaxN(1e6+5);
pair<int,int> point[MaxN];
map<pair<int,int>,int> val;
int n,k;
struct T
{
    vector<int> nums;
    int sz;
    int lowbit(int a){return a&(-a);}
    int query(int index)
    {
        int res(0);
        while(index)
        {
            res+=nums[index];
            index-=lowbit(index);
        }
        return res;
    }
    void update(int index,int val)
    {
        while(index<=sz)
        {
            nums[index]+=val;
            index+=lowbit(index);
        }
    }
    T(int n)
    {
        nums.resize(n+1);
        sz=n;
    }
    void clear()
    {
        nums.assign(sz,0);
    }
};
void solve()
{
    
}
signed main()
{
    ios::sync_with_stdio(false);
    int _;
    _=1;
    cin>>_;
    while(_--)solve();
}