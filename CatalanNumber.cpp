#include <bits/stdc++.h>
#define inc(i,a,b) for(int i(a);i<=b;i++)
using namespace std;

const int mod = 998244353;
const int MAX = 4e5 + 42;

int fact[MAX], inv[MAX], inv_fact[MAX];

int C(int n, int k) {
    if(n < k || k < 0) return 0;
    return (long long) fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
}

int Cat(int n) {
    return (long long) C(2 * n, n) * inv[n + 1] % mod;
}

int binpow(int x, int n) {
    int ans = 1;
    while(n) {
        if(n & 1) ans = (long long) ans * x % mod;
        n >>= 1;
        x = (long long) x * x % mod;
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int initial_m = m;
    vector<pair<int, int>> a(m);
    for(auto &[l, r] : a) {
        cin >> l >> r;
    }
    bool was_full = 0;
    vector<int> was_single(n + 1);
    for(auto [l, r] : a) was_full |= (r - l + 1 == n);
    for(auto [l, r] : a) {
        if(l == r) was_single[l] = 1;
    }
    if(!was_full) {
        a.push_back({1, n});
        m++;
    }
    for(int i = 1; i <= n; i++) {
        if(!was_single[i] && n != 1) {
            a.push_back({i, i});
            m++;
        }
    }
    for(auto &[l, r] : a) r = -r;
    sort(a.begin(), a.end());
    vector<int> deg(m);
    for(int i = 0; i < m; i++) {
        int j = i + 1;
        while(j < m) {
            if(-a[i].second < a[j].first) break;
            deg[i]++;
            j = upper_bound(a.begin(), a.end(), make_pair(-a[j].second, 1)) - a.begin();
        }
    }
    for(auto &[l, r] : a) r = -r;
    int ans = 1;
    for(int i = 0; i < m; i++) {
        if(deg[i] > 0) {
            assert(deg[i] >= 2);
            ans = (long long) ans * Cat(deg[i] - 1) % mod;
        }
    }
    cout << ans << '\n';
}

signed main() {
    fact[0] = 1;
    for(int i = 1; i < MAX; i++) fact[i] = (long long) fact[i - 1] * i % mod;
    inv_fact[MAX - 1] = binpow(fact[MAX - 1], mod - 2);
    for(int i = MAX - 1; i; i--) inv_fact[i - 1] = (long long) inv_fact[i] * i % mod;
    assert(inv_fact[0] == 1);
    for(int i = 1; i < MAX; i++) inv[i] = (long long) inv_fact[i] * fact[i - 1] % mod;
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int ttt = 1;
    cout<<binpow(2,mod-1)<<endl;
    inc(i,1,10)cout<<Cat(i)<<" ";cout<<endl;
    // cin >> ttt;
    // while(ttt--) {
    //     solve();
    // }
    system("pause");
}