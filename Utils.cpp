// 必备板子
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)

// 字符串哈希中常用模
const int Mod1=998244353ll;
const int Mod2=1004535809ll;

// 方便本地调试的板子
#define LOCAL
#ifdef LOCAL
ostream &operator<< (ostream & o,const pair<int,int> a)
{
    o<<"{"<<a.first<<","<<a.second<<"}";
    return o;
}
#define split cout<<"-------------------------------"<<endl
#define debug0(c) cout<<"[DEBUG] "<<#c<<"="<<c<<endl
#define debug1(c,l,r)\
cout<<"[DEBUG] "<<#c<<": ";\
inc(i,l,r)cout<<c[i]<<" ";cout<<endl 
#define debug2(c,l,r,ll,rr)\
cout<<"[DEBUG] "<<#c<<endl;\
inc(i,l,ll){inc(j,r,rr)cout<<c[i][j]<<" ";cout<<endl;}
#define T test()
#define case_ans cout<<"[ANSWER] "
#else
#define T
#define case_ans
#define split
#define debug0(c)
#define debug1(c,l,r)
#define debug2(c,l,r,ll,rr)
#endif



// 并查集板子
struct DSU {
    std::vector<int> f, siz;
    
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }
    
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    
    int size(int x) {
        return siz[find(x)];
    }
};

// 输出int128板子
string int128ToString(__int128 x) {
  if (x == 0) return "0";
  string result;
  bool is = x < 0;
  if (is) x = -x;
  while (x > 0) {
    result.push_back('0' + (x % 10));
    x /= 10;
  }
  if (is) result.push_back('-');
  reverse(result.begin(), result.end());
  return result;
}

// 用于处理凸包的板子
namespace HullUtil
{
    const double HULL_UTIL_EPS(1e-8);
    // 定义向量
    struct Vector{
        double x,y;
        // 向量内积
        double operator* (Vector v){
            return x*v.x+y*v.y;
        }
        // 获得垂直向量
        Vector getVertical()
        {
            return {y,-x};
        }
    };
    // 定义点
    struct Point{
        double x,y;
        // 点获取向量
        Vector operator- (Point p2){
            Vector res;
            res.x=x-p2.x;
            res.y=y-p2.y;
            return res;
        }
    };
    // 定义点的输出流
    ostream &operator<<(ostream& o,const Point& p){
        o<<"["<<p.x<<","<<p.y<<"]";
        return o;
    }   

    // 向量外积
    double intersection(Vector v1,Vector v2){return v1.x*v2.y-v1.y*v2.x;}
    // 三点外积
    double cross(Point p1,Point p2,Point p3){return intersection(p2-p1,p3-p2);}
    // 向量的模
    double abs(Vector v){return sqrtl(v.x*v.x+v.y*v.y);}
    // 两点之间的距离
    double getDist(Point p1,Point p2){return abs(p2-p1);}

    // 定义线
    struct Line{
        Point p;
        Vector v;
        // 获取线和点之间的距离
        double getDist(Point a){return fabsl(intersection(p-a,v))/abs(v);}
    };
    // 直线交点
    Point getIntersection(Line line1,Line line2)
    {
        double cross_product = intersection(line1.v, line2.v);
        // 直线平行
        if (fabsl(cross_product) < HULL_UTIL_EPS) {
            return {NAN, NAN};
        }

        Vector v_diff = line2.p-line1.p;
        double t_numerator = intersection(v_diff, line2.v);
        double t = t_numerator / cross_product;
        Point intersection_point;
        intersection_point.x = line1.p.x + t * line1.v.x;
        intersection_point.y = line1.p.y + t * line1.v.y;
        return intersection_point;
    }
    // 两点之间求直线
    Line getLine(Point p1,Point p2){return {p1,p2-p1};}

    // 凸包结构体
    struct Hull{
        // 所有点
        vector<Point> p;
        // 凸包、上凸包、下凸包
        vector<Point> hull,upper,lower;
        double diameter;
        Hull(vector<pair<double,double>> in){
            diameter=0;
            if(in.empty())return;
            sort(in.begin(),in.end());
            for(auto[x,y]:in)p.push_back({x,y});
            // 求下凸包
            vector<Point> ss;
            ss.push_back(p[0]);
            inc(i,1,p.size()-1)
            {
                while(ss.size()>1&&cross(ss[ss.size()-2],ss[ss.size()-1],p[i])<=0)ss.pop_back();
                ss.push_back(p[i]);
            }
            lower.swap(ss);
            // 求上凸包
            reverse(p.begin(),p.end());
            ss.push_back(p[0]);
            inc(i,1,p.size()-1)
            {
                while(ss.size()>1&&cross(ss[ss.size()-2],ss[ss.size()-1],p[i])<=0)ss.pop_back();
                ss.push_back(p[i]);
            }
            upper.swap(ss);
            // 求凸包
            inc(i,0,lower.size()-2)hull.push_back(lower[i]);
            inc(i,0,upper.size()-2)hull.push_back(upper[i]);
            reverse(p.begin(),p.end());
        }
        // 求凸包直径
        double getDiameter()
        {
            if(diameter>HULL_UTIL_EPS)return diameter;
            int sz=hull.size();
            auto nxt=[sz](int a)->int{return (a+1)%sz;};
            int cur(1);
            inc(i,0,hull.size()-1)
            {
                Line bottom(getLine(hull[i],hull[nxt(i)]));
                while(bottom.getDist(hull[cur])<bottom.getDist(hull[nxt(cur)])){cur=nxt(cur);}
                diameter=max({diameter,getDist(hull[cur],hull[i]),getDist(hull[nxt(cur)],hull[i])});                
            }
            return diameter;
        }
        // 判断点是否在凸包内
        bool contain(Point p){
            inc(i,0,hull.size()-1)
            {
                Point p1,p2;
                if(!i)p1=hull.back(),p2=hull.front();
                else p1=hull[i-1],p2=hull[i];
                if(cross(p,p1,p2)<0)return false;
            }
            return true;
        }
    };
}

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

void solve()
{

}
// 用于在程序启动前预先测试
void test()
{

}
signed main()
{
    T;
    ios::sync_with_stdio(false);
    int _;
    _=1;
    cin>>_;
    while(_--)
    {
        // 样例分隔符，仅在#define LOCAL时生效
        split;
        solve();
    }
}
