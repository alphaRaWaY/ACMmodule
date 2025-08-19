#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define inc(i,a,b) for(int i(a);i<=b;i++)
#define dec(i,a,b) for(int i(a);i>=b;i--)
namespace nttUtil{

    const int G = 3, Gi = 332748118; 
    int limit(1), L(0);    
    vector<int> r;

    void init()
    {
        r.clear();
        limit = 1;
        L = 0;
    }
    
    inline int fastpow(int a, int k, int mod) {
        int base = 1;
        while(k) {
            if(k & 1) base = (base * a) % mod;
            a = (a * a) % mod;
            k >>= 1;
        }
        return base % mod;
    }
    
    /***************************************** 
     * 取模意义下多项式相乘
    */

    /**
     * @param A 多项式
     * @param type 方向
     * @param mod 模
     */
    inline void NTT(vector<int> &A, int type, int mod) {
        for(int i = 0; i < limit; i++) 
        if(i < r[i]) swap(A[i], A[r[i]]);
        for(int mid = 1; mid < limit; mid <<= 1) {    
            int Wn = fastpow( type == 1 ? G : Gi , (mod - 1) / (mid << 1),mod);
            for(int j = 0; j < limit; j += (mid << 1)) {
                int w = 1;
                for(int k = 0; k < mid; k++, w = (w * Wn) % mod) {
                    int x = A[j + k], y = w * A[j + k + mid] % mod;
                    A[j + k] = (x + y) % mod,
                    A[j + k + mid] = (x - y + mod) % mod;
                }
            }
        }
    }

    /**
     * @param nums1 多项式1
     * @param nums1 多项式2
     * @param mod 模
     */
    vector<int> mul(vector<int> nums1, vector<int> nums2, int mod)
    {
        vector<int> res;
        int N(nums1.size()-1);        
        int M(nums2.size()-1);        
        init();
        
        while(limit <= N + M) limit <<= 1, L++;

        nums1.resize(limit);
        nums2.resize(limit);
        res.resize(limit);
        r.resize(limit);
        
        for(int i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));    
        
        NTT(nums1, 1, mod);NTT(nums2, 1, mod);  
        for(int i = 0; i < limit; i++) res[i] = (nums1[i] * nums2[i]) % mod;
        NTT(res, -1, mod);    
        int inv = fastpow(limit, mod - 2, mod);
        for(int i = 0; i <= N + M; i++)
            res[i] = (res[i] * inv) % mod;
        res.resize(N+M+1);
        return res;
    }
};
const int MOD(998244353);
int n, m;
vector<int> nums1,nums2;
void solve()
{
    cin>>n>>m;
    nums1.resize(n+1);
    nums2.resize(m+1);
    for(int& tmp:nums1)cin>>tmp;
    for(int& tmp:nums2)cin>>tmp;
    vector<int> ans = nttUtil::mul(nums1,nums2,MOD);
    for(int tmp:ans)cout<<tmp<<" ";cout<<endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    int _;
    cin>>_;
    while(_--)solve();
    return 0;
}
/*
1
2 3
1 2 3
1 2 3 4
*/