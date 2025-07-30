// 树链剖分
#include<bits/stdc++.h>
using namespace std;
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)
#define endl '\n'
// #define LOCAL

#ifdef LOCAL
#define debug0(c)cout<<"[DEBUG] "<<#c<<": "<<c<<endl
#define debug1(c,l,r)cout<<"[DEBUG] "<<#c<<": ";inc(i,l,r)cout<<c[i]<<" ";cout<<endl
#else
#define debug0(c)
#define debug1(c,l,r)
#endif

// 树链剖分模板
struct HDL{
    /**
     * 树的尺寸
     * 树的根
     */
    int size,root;
    /**
     * fa：父亲结点
     * siz：子树大小
     * top：当前重链的顶端
     * son：重儿子
     * dep：深度
     * dfn：dfs序
     * rnk：响应dfs序上的结点
     */
    vector<int> fa,siz,top,son,dep,dfn,rnk;
    /**
     * 邻接链表
     */
    vector<vector<int> >ed;
    
    HDL(int size){
        this->size=size;
        ed.assign(size+1,{});
        
        fa.resize(size+1);
        siz.resize(size+1);
        son.resize(size+1);
        dep.resize(size+1);
        
        dfn.resize(size+1);
        rnk.resize(size+1);
        top.resize(size+1);
    }
    void addEdge(int a,int b)
    {
        ed[a].push_back(b);
        ed[b].push_back(a);
    }
    void build(int root)
    {
        int cnt(0);
        dfs1(root,0);
        dfs2(root,root,cnt);
    }
    int dfs1(int index,int pa)
    {
        siz[index]=1;
        fa[index]=pa;
        dep[index]=dep[pa]+1;
        for(int tmp:ed[index])
        {
            if(tmp==pa)continue;
            int csz = dfs1(tmp,index);
            siz[index] += csz;
            if(!son[index]||csz>siz[son[index]])son[index]=tmp;
        }
        return siz[index];
    }
    void dfs2(int index,int root,int& cnt)
    {
        top[index]=root;
        dfn[index]=++cnt;
        rnk[cnt]=index;
        if(son[index])dfs2(son[index],root,cnt);
        for(int tmp:ed[index])
        {
            if(tmp==fa[index]||tmp==son[index])continue;
            else dfs2(tmp,tmp,cnt);
        }
    }
    int lca(int a,int b)
    {
        while(top[a]!=top[b])
        {
            if(dep[top[a]]<dep[top[b]])swap(a,b);
            a=fa[top[a]];   
        }
        return dep[a]<dep[b]?a:b;
    }
    // 路过多少条边
    int dist(int a,int b)
    {
        return dep[a]+dep[b]-2*dep[lca(a,b)];
    }
    // 是否经过某一点
    bool pass(int begin,int end,int p)
    {
        return dist(begin,p)+dist(end,p)==dist(begin,end);
    }
    // 是否经过某一条边
    bool pass(int begin,int end,pair<int,int> p)
    {
        auto[u,v]=p;
        return (dist(begin,u)+dist(end,v)+1==dist(begin,end))
        ||(dist(begin,v)+dist(end,u)+1==dist(begin,end));
    }
    
};

int n,m,root;
void solve()
{
    cin>>n>>m>>root;
    HDL t(n);
    inc(i,1,n-1)
    {
        int a,b;
        cin>>a>>b;
        t.addEdge(a,b);
    }
    t.build(root);
    while(m--)
    {
        int a,b;
        cin>>a>>b;
        cout<<t.lca(a,b)<<endl;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    int _;
    _=1;
    // cin>>_;
    while(_--)solve();
}
/*
5 5 4

3 1
2 4
5 1
1 4

2 4
3 2
3 5
1 2
4 5

4
4
1
4
4
*/