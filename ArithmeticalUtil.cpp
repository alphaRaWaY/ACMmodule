// 必备板子
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define double long double
#define endl '\n'
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)
// 方便本地调试的板子
// #define LOCAL
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
// 数论板子
namespace arithmetical{
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
     * 欧拉筛
     * @param n 筛选质数最大不超过n
     */
    vector<int> primes,pp;//质数、最小质因子
    void initPrime(int n)
    {
        primes.clear();
        pp.assign(n+5,0);
        inc(i,2,n)
        {
            if(!pp[i])primes.push_back(i);
            for(int tmp:primes)
            {
                if(tmp*i>n)break;
                pp[tmp*i]=tmp;
                if(i%tmp==0)break;
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
    // P1226 快速幂
    /*
    int a,b,c;
    cin>>a>>b>>c;
    cout<<a<<'^'<<b<<" mod "<<c<<'='<<arithmetical::qpow(a,b,c)<<endl;
    */

    // P3383 线性筛素数
    /*
    int n,q;
    cin>>n>>q;
    // 注意内存，n最大为1e8，如果使用long long会导致最大内存达到800mb
    arithmetical::initPrime(n);
    while(q--){int tmp;cin>>tmp;cout<<arithmetical::primes[tmp-1]<<endl;}
    */
    
    // P3811 乘法逆元
    /*
    int n,p;
    cin>>n>>p;
    arithmetical::initInv(n,p);
    inc(i,1,n)cout<<arithmetical::inv[i]<<endl;
    */

    // P1495 中国剩余定理（注意，这题卡long long，需要__int128）
    /*
    int n;
    cin>>n;
    map<int,int> cnt;
    inc(i,1,n)
    {
        int a,b;
        cin>>a>>b;
        cnt[a]=b;
    }
    cout<<arithmetical::CRT(cnt)<<endl;
    */

    // 扩展欧几里得求逆元
    /*
    int a,b;
    cin>>a>>b;
    cout<<arithmetical::getInv_gcd(a,b)<<endl;
    */

    
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
    // cin>>_;
    while(_--)
    {
        // 样例分隔符，仅在#define LOCAL时生效
        split;
        solve();
    }
}
