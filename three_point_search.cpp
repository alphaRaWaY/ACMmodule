#include <bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define int long long
#define double long double
#define endl '\n'
#define inc(i, a, b) for (int i(a); i <= b; i++)
#define dec(i, a, b) for (int i(a); i >= b; i--)
#define ALL(x) x.begin(), x.end()
#define INF 0x3f3f3f3f
#define Mod1 998244353
#define Mod2 1004535809
inline int rs(int r){return r<<1|1;}
inline int ls(int r){return r<<1;}
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
const double eps=1e-7;
const int MAXN(15);
double a[MAXN]; 
int n;
double l,r;
double F(double x)
{
    double ans(0);
    inc(i,1,n+1)
    {
        ans=ans*x+a[i];
    }
    return ans;
}
void solve() 
{
    cin>>n>>l>>r;
    inc(i,1,n+1)cin>>a[i];
    // inc(i,-5,10)cout<<F(-0.1*i)<<endl;
    while(fabs(r-l)>eps)
    {
        double mid((r+l)/2);
        if(F(mid+eps)>F(mid-eps)) l=mid;
        else    r=mid;
    }
    printf("%.5LF\n",r);
}
signed main() {
  ios::sync_with_stdio(false);
  int _;
  _=1;
//   cin >> _;
  while (_--) solve();
    system("pause");
}