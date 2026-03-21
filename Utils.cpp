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
#define case_ans cout<<"[ANSWER] "
#else
#define T
#define case_ans
#define split
#define debug0(c)
#define debug1(c,l,r)
#define debug2(c,l,r,ll,rr)
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

const int MAXN(405);
const double eps(1e-8);
double matrix[MAXN][MAXN];
/**
 * 高斯消元，消除下三角
 * (long double)matrix   需要消元的矩阵
 * (int)n    方阵的大小
 * 最后计算det(matrix)只需要将对角线的所有数字相乘即可
 */
void gauss(int n)
{
    inc(j,1,n-1)
    {
        if(fabs(matrix[j][j])<eps)
        {
            int target(0);
            inc(i,j+1,n)
            {
                if(fabs(matrix[i][j])>=eps)
                {
                    target=i;
                    break;
                }
            }
            if(target)
            {
                inc(k,1,n)
                {
                    matrix[j][k]*=-1;   
                    swap(matrix[j][k],matrix[target][k]);
                }
            }
            else continue;
        }
        inc(i,j+1,n)
        {
            double tmp=matrix[i][j]/matrix[j][j];
            inc(k,1,n)
            {
                matrix[i][k]-=matrix[j][k]*tmp;
            }
        }
    }
}

// 数论板子
namespace arithmetical{
    /***常用公式
     * 欧拉定理
     * if(__gcd(a,m)==1)
     */

    // 随机数
    mt19937_64 rng(time(0));
    /**
     * 在一定范围内获取随机数
     * @param l 闭区间左端点
     * @param r 闭区间右端点
     */
    int getRand(int l,int r)
    {
        return rng()%(r-l+1)+l;
    }
    /**
     * 安全取模（防止负数）
     * @param a 待取模的数
     * @param p 模数
     */
    int safeMod(int a,int p)
    {
        return (a%p+p)%p;
    }
    /**
     * 快加
     * @param a 加数1
     * @param b 加数2
     * @param mod 模
     */
    int qadd(int a,int b,int mod)
    {
        return (a+b)%mod;
    }
    /**
     * 快乘
     * @param a 乘数1
     * @param b 乘数2
     * @param mod 模
     */
    int qmul(int a,int b,int mod)
    {
        int c=(double)a/mod*b;
        int res=(unsigned int)a*b-(unsigned int)c*mod;
        return (res+mod)%mod;
    }
    /**
     * 快速幂
     * @param a 底数
     * @param n 指数
     * @param mod 模
     */
    int qpow(int a,int n,int mod)
    {
        int res=1;
        while(n)
        {
            if(n&1) res=qmul(res,a,mod);
            a=qmul(a,a,mod);
            n>>=1;
        }
        return res;
    }
    /**
     * Miller Rabin Test
     * @param n 检测n是否为素数
     * @return 为素数返回true 
     */
    bool millerRabin(int n)
    {
        if(n<3||n%2==0) return n==2;//特判
        int u=n-1,t=0;
        while(u%2==0) u/=2,++t;
        int ud[]={2,325,9375,28178,450775,9780504,1795265022};
        for(int a:ud)
        {
            int v=qpow(a,u,n);
            if(v==1||v==n-1||v==0) continue;
            for(int j=1;j<=t;j++)
            {
                v=qmul(v,v,n);
                if(v==n-1&&j!=t){v=1;break;}//出现一个n-1，后面都是1，直接跳出
                if(v==1) return 0;//这里代表前面没有出现n-1这个解，二次检验失败
            }
            if(v!=1) return 0;//Fermat检验
        }
        return 1;
    }
    /**
     * 倍增优化的Pollard_Rho
     * @param x 求x的非平凡因子
     * @return 可能返回x本身
     */
    int Pollard_Rho(int x) {
        auto f = [](int t,int c,int x)->int{
            return (t*t%x+c)%x;
        };
        int t = 0;
        int c = rand() % (x - 1) + 1;
        int s = t;
        int step = 0, goal = 1;
        int val = 1;
        for (goal = 1;; goal <<= 1, s = t, val = 1) {
            for (step = 1; step <= goal; ++step) {
                t = f(t, c, x);
                val = val * abs(t - s) % x;
                // 如果 val 为 0，退出重新分解
                if (!val) return x;
                if (step % 127 == 0) {
                    int d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            int d = gcd(val, x);
            if (d > 1) return d;
        }
    }
    /**
     * 欧拉函数
     */
    int euler_phi(int n) {
        int ans=n;
        for (int i(2);i*i<=n;i++)
        if (n%i==0) 
        {
            ans=ans/i*(i-1);
            while (n%i==0)n/=i;
        }
        if(n>1)ans=ans/n*(n-1);
        return ans;
    }
    /**
     * 预处理因数
     * @param n 预处理的范围
     */
    vector<vector<int>> factors;
    void initFactor(int n)
    {
        factors.assign(n+1,vector<int>(1,1));
        inc(i,2,n)
        {
            for(int j(i);j<=n;j+=i)factors[j].push_back(i);
        }
    }
    /**
     * 加强欧拉筛
     * 线性筛选
     * 质数
     * 最小质因子
     * 欧拉函数
     * @param n 筛选质数最大不超过n
     */
    vector<int> primes,pp,phi;//质数、最小质因子、欧拉函数
    void initPrime(int n)
    {
        // 筛质数初始化
        primes.clear();
        // 筛欧拉函数初始化
        phi.assign(n+5,0);
        // 筛最小质因子初始化
        pp.assign(n+5,0);
        inc(i,2,n)
        {
            if(!pp[i])
            {
                // 筛质数
                primes.push_back(i);
                // 筛欧拉函数
                phi[i]=i-1;
            }
            for(int tmp:primes)
            {
                if(tmp*i>n)break;
                // 筛最小质因子
                pp[tmp*i]=tmp;
                // 欧拉筛线性优化
                if(i%tmp==0)
                {
                    // 筛欧拉函数
                    phi[i*tmp]=phi[i]*tmp;
                    break;
                }
                phi[i*tmp]=phi[i]*phi[tmp];
            }
        }
    }
    
    /**
     * 质因数分解欧拉筛范围内的数
     * @param a 待质因数分解的数
     * @param cnt 质因数
     */
    void getPrimeFac(int a,map<int,int>& cnt)
    {
        while(pp[a])
        {
            // debug0(a);
            cnt[pp[a]]++;
            a/=pp[a];        
        }
        cnt[a]++;
    }
    /**
     * 质因数分解欧拉筛范围外的数
     * @param a 待质因数分解的数
     * @param cnt 质因数
     */
    void __getPrimeFac64(int a,map<int,int>& cnt)
    {
        if(millerRabin(a))
        {
            cnt[a]++;
            return;
        }
        if(a<=1e7)
        {
            getPrimeFac(a,cnt);
            return;
        }
        int tmp=Pollard_Rho(a);
        __getPrimeFac64(a/tmp,cnt);
        __getPrimeFac64(tmp,cnt);
    }
    /**
     * 扩展欧几里得
     * 求ax+by=gcd(a,b)的一组x，y解
     */
    void exgcd(int a,int b,int &x,int &y)
    {
        if(b==0)
        {
            x=1;
            y=0;
        }
        else
        {
            exgcd(b,a%b,x,y);
            int tmp = x;
            x = y;
            y = tmp-(a/b)*y;
        }
    }
    /**
     * 费马小求逆元
     * @param n 逆元数组尺寸
     * @param mod 模
     */
    int getInv(int a,int p){return qpow(a,p-2,p);}
    /**
     * 线性法求逆元
     * @param n 逆元数组尺寸
     * @param mod 模
     */
    vector<int> inv;//逆元数组
    void initInv(int n,int mod)
    {
        inv.assign(n+5,0);
        inv[1]=1;
        inc(i,2,n)
        {
            inv[i]=((mod-mod/i)*inv[mod%i])%mod;
        }
    }
    /**
     * 扩展欧几里得求逆元
     * @param a 求逆元的数
     * @param mod 模
     */
    int getInv_gcd(int a,int mod)
    {
        int x,y;
        exgcd(a,mod,x,y);
        x=(mod+x%mod)%mod;
        return x;
    }
    /**
     * 初始化阶乘数组
     * @param n 数组大小
     * @param p 模
     */
    vector<int> fac,invFac;//阶乘与阶乘的逆元
    void initFac(int n,int p)
    {
        fac.assign(n+5,1);
        invFac.assign(n+5,1);
        inc(i,2,n)fac[i]=fac[i-1]*i%p;
        invFac[n]=getInv(fac[n],p);
        dec(i,n-1,1)invFac[i]=invFac[i+1]*(i+1)%p;
    }
    /**
     * 组合数
     * 使用前先初始化阶乘数组
     * @param n C的下面
     * @param k C的上面
     * @param mod 模
     */
    int C(int n,int k,int mod) {
        if(n < k || k < 0) return 0;
        return fac[n]*invFac[k]%mod*invFac[n-k]%mod;
    }   
    /**
     * 卡特兰数
     * 凸多边形三角划分
     * 在圆上选择2n个点,将这些点成对连接起来使得所得到的n条线段不相交的方法数
     * 序列个数为n的出栈序列种数
     * 给定节点组成二叉搜索树
     * n对括号正确匹配数目
     * @param n 
     * @param mod 模
     */
    int Cat(int n,int mod) {
        return C(2*n,n,mod)*inv[n+1]%mod;
    }
    /**
     * 中国剩余定理
     * @param cnt 各大质数的剩余系  
     */
    int CRT(map<int,int> cnt)
    {
        int x=cnt.size();
        int total(1);
        vector<int> n(x+5),a(x+5);
        vector<__int128> m(x+5),c(x+5);
        int i=0;
        for(auto[x,y]: cnt)
        {
            i++;
            n[i]=x;
            a[i]=y;
            total*=n[i];
        }
        inc(i,1,x)
        {
            m[i]=total/n[i];
            // 为了防止n[i]不是质数的情况，使用扩展欧几里得方法求逆元而不是费马小
            c[i]=m[i]*getInv_gcd(m[i],n[i]);
        }
        int ans(0);
        inc(i,1,x)
        {
            ans=(c[i]*a[i]%total+ans)%total;
        }
        return (ans%total+total)%total;
    } 
}

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

// 树状数组
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

// 数论板子
namespace arithmetical{
    /***常用公式
     * 欧拉定理
     * if(__gcd(a,m)==1)
     */

    // 随机数
    mt19937_64 rng(time(0));
    /**
     * 在一定范围内获取随机数
     * @param l 闭区间左端点
     * @param r 闭区间右端点
     */
    int getRand(int l,int r)
    {
        return rng()%(r-l+1)+l;
    }
    /**
     * 安全取模（防止负数）
     * @param a 待取模的数
     * @param p 模数
     */
    int safeMod(int a,int p)
    {
        return (a%p+p)%p;
    }
    /**
     * 快加
     * @param a 加数1
     * @param b 加数2
     * @param mod 模
     */
    int qadd(int a,int b,int mod)
    {
        return (a+b)%mod;
    }
    /**
     * 快乘
     * @param a 乘数1
     * @param b 乘数2
     * @param mod 模
     */
    int qmul(int a,int b,int mod)
    {
        int c=(double)a/mod*b;
        int res=(unsigned int)a*b-(unsigned int)c*mod;
        return (res+mod)%mod;
    }
    /**
     * 快速幂
     * @param a 底数
     * @param n 指数
     * @param mod 模
     */
    int qpow(int a,int n,int mod)
    {
        int res=1;
        while(n)
        {
            if(n&1) res=qmul(res,a,mod);
            a=qmul(a,a,mod);
            n>>=1;
        }
        return res;
    }
    /**
     * Miller Rabin Test
     * @param n 检测n是否为素数
     * @return 为素数返回true 
     */
    bool millerRabin(int n)
    {
        if(n<3||n%2==0) return n==2;//特判
        int u=n-1,t=0;
        while(u%2==0) u/=2,++t;
        int ud[]={2,325,9375,28178,450775,9780504,1795265022};
        for(int a:ud)
        {
            int v=qpow(a,u,n);
            if(v==1||v==n-1||v==0) continue;
            for(int j=1;j<=t;j++)
            {
                v=qmul(v,v,n);
                if(v==n-1&&j!=t){v=1;break;}//出现一个n-1，后面都是1，直接跳出
                if(v==1) return 0;//这里代表前面没有出现n-1这个解，二次检验失败
            }
            if(v!=1) return 0;//Fermat检验
        }
        return 1;
    }
    /**
     * 倍增优化的Pollard_Rho
     * @param x 求x的非平凡因子
     * @return 可能返回x本身
     */
    int Pollard_Rho(int x) {
        auto f = [](int t,int c,int x)->int{
            return (t*t%x+c)%x;
        };
        int t = 0;
        int c = rand() % (x - 1) + 1;
        int s = t;
        int step = 0, goal = 1;
        int val = 1;
        for (goal = 1;; goal <<= 1, s = t, val = 1) {
            for (step = 1; step <= goal; ++step) {
                t = f(t, c, x);
                val = val * abs(t - s) % x;
                // 如果 val 为 0，退出重新分解
                if (!val) return x;
                if (step % 127 == 0) {
                    int d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            int d = gcd(val, x);
            if (d > 1) return d;
        }
    }
    /**
     * 欧拉函数
     */
    int euler_phi(int n) {
        int ans=n;
        for (int i(2);i*i<=n;i++)
        if (n%i==0) 
        {
            ans=ans/i*(i-1);
            while (n%i==0)n/=i;
        }
        if(n>1)ans=ans/n*(n-1);
        return ans;
    }
    /**
     * 预处理因数
     * @param n 预处理的范围
     */
    vector<vector<int>> factors;
    void initFactor(int n)
    {
        factors.assign(n+1,vector<int>(1,1));
        inc(i,2,n)
        {
            for(int j(i);j<=n;j+=i)factors[j].push_back(i);
        }
    }
    /**
     * 加强欧拉筛
     * 线性筛选
     * 质数
     * 最小质因子
     * 欧拉函数
     * @param n 筛选质数最大不超过n
     */
    vector<int> primes,pp,phi;//质数、最小质因子、欧拉函数
    void initPrime(int n)
    {
        // 筛质数初始化
        primes.clear();
        // 筛欧拉函数初始化
        phi.assign(n+5,0);
        // 筛最小质因子初始化
        pp.assign(n+5,0);
        inc(i,2,n)
        {
            if(!pp[i])
            {
                // 筛质数
                primes.push_back(i);
                // 筛欧拉函数
                phi[i]=i-1;
            }
            for(int tmp:primes)
            {
                if(tmp*i>n)break;
                // 筛最小质因子
                pp[tmp*i]=tmp;
                // 欧拉筛线性优化
                if(i%tmp==0)
                {
                    // 筛欧拉函数
                    phi[i*tmp]=phi[i]*tmp;
                    break;
                }
                phi[i*tmp]=phi[i]*phi[tmp];
            }
        }
    }
    
    /**
     * 质因数分解欧拉筛范围内的数
     * @param a 待质因数分解的数
     * @param cnt 质因数
     */
    void getPrimeFac(int a,map<int,int>& cnt)
    {
        while(pp[a])
        {
            // debug0(a);
            cnt[pp[a]]++;
            a/=pp[a];        
        }
        cnt[a]++;
    }
    /**
     * 质因数分解欧拉筛范围外的数
     * @param a 待质因数分解的数
     * @param cnt 质因数
     */
    void __getPrimeFac64(int a,map<int,int>& cnt)
    {
        if(millerRabin(a))
        {
            cnt[a]++;
            return;
        }
        if(a<=1e7)
        {
            getPrimeFac(a,cnt);
            return;
        }
        int tmp=Pollard_Rho(a);
        __getPrimeFac64(a/tmp,cnt);
        __getPrimeFac64(tmp,cnt);
    }
    /**
     * 扩展欧几里得
     * 求ax+by=gcd(a,b)的一组x，y解
     */
    void exgcd(int a,int b,int &x,int &y)
    {
        if(b==0)
        {
            x=1;
            y=0;
        }
        else
        {
            exgcd(b,a%b,x,y);
            int tmp = x;
            x = y;
            y = tmp-(a/b)*y;
        }
    }
    /**
     * 费马小求逆元
     * @param n 逆元数组尺寸
     * @param mod 模
     */
    int getInv(int a,int p){return qpow(a,p-2,p);}
    /**
     * 线性法求逆元
     * @param n 逆元数组尺寸
     * @param mod 模
     */
    vector<int> inv;//逆元数组
    void initInv(int n,int mod)
    {
        inv.assign(n+5,0);
        inv[1]=1;
        inc(i,2,n)
        {
            inv[i]=((mod-mod/i)*inv[mod%i])%mod;
        }
    }
    /**
     * 扩展欧几里得求逆元
     * @param a 求逆元的数
     * @param mod 模
     */
    int getInv_gcd(int a,int mod)
    {
        int x,y;
        exgcd(a,mod,x,y);
        x=(mod+x%mod)%mod;
        return x;
    }
    /**
     * 初始化阶乘数组
     * @param n 数组大小
     * @param p 模
     */
    vector<int> fac,invFac;//阶乘与阶乘的逆元
    void initFac(int n,int p)
    {
        fac.assign(n+5,1);
        invFac.assign(n+5,1);
        inc(i,2,n)fac[i]=fac[i-1]*i%p;
        invFac[n]=getInv(fac[n],p);
        dec(i,n-1,1)invFac[i]=invFac[i+1]*(i+1)%p;
    }
    /**
     * 组合数
     * 使用前先初始化阶乘数组
     * @param n C的下面
     * @param k C的上面
     * @param mod 模
     */
    int C(int n,int k,int mod) {
        if(n < k || k < 0) return 0;
        return fac[n]*invFac[k]%mod*invFac[n-k]%mod;
    }   
    /**
     * 卡特兰数
     * 凸多边形三角划分
     * 在圆上选择2n个点,将这些点成对连接起来使得所得到的n条线段不相交的方法数
     * 序列个数为n的出栈序列种数
     * 给定节点组成二叉搜索树
     * n对括号正确匹配数目
     * @param n 
     * @param mod 模
     */
    int Cat(int n,int mod) {
        return C(2*n,n,mod)*inv[n+1]%mod;
    }
    /**
     * 中国剩余定理
     * @param cnt 各大质数的剩余系  
     */
    int CRT(map<int,int> cnt)
    {
        int x=cnt.size();
        int total(1);
        vector<int> n(x+5),a(x+5);
        vector<__int128> m(x+5),c(x+5);
        int i=0;
        for(auto[x,y]: cnt)
        {
            i++;
            n[i]=x;
            a[i]=y;
            total*=n[i];
        }
        inc(i,1,x)
        {
            m[i]=total/n[i];
            // 为了防止n[i]不是质数的情况，使用扩展欧几里得方法求逆元而不是费马小
            c[i]=m[i]*getInv_gcd(m[i],n[i]);
        }
        int ans(0);
        inc(i,1,x)
        {
            ans=(c[i]*a[i]%total+ans)%total;
        }
        return (ans%total+total)%total;
    } 
}

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
