#include <bits/stdc++.h>
using namespace std;
using pii=pair<int,int>;
#define int long long
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
void solve() 
{
    
}
signed main() {
  ios::sync_with_stdio(false);
  int _;
  cin >> _;
  while (_--) solve();
}