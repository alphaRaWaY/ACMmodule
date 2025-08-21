#include<bits/stdc++.h>
#define ri int
#define f first
#define s second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 5e5 + 10;
int n, m, x, y, root;
struct LCA
{
	vector<int> g[N];
    int n, dep[N], anc[N][30]; //注意要开log2(n), 需根据题目调整

    void init(int _n)
    {
        n = _n;
        for (ri i = 1; i <= n; i++)
        {
            dep[i] = 0; g[i].clear();
            for (ri j = 0; j < 25; j++) anc[i][j] = 0;
        }
    }
    void add_edge(int x, int y) { g[x].pb(y); g[y].pb(x); }
    void dfs(int x, int fa)
    {
        anc[x][0] = fa, dep[x] = dep[fa] + 1;
        for (ri i = 1; i <= __lg(dep[x]); i++) anc[x][i] = anc[anc[x][i - 1]][i - 1];
        for (auto y : g[x]) if (y != fa) dfs(y, x);
    }
    int lca(int x, int y)
    {
        if (dep[x] < dep[y]) swap(x, y);
        while (dep[x] > dep[y]) x = anc[x][__lg(dep[x] - dep[y])];
        if (x == y) return x;
        for (ri i = __lg(dep[x]); i >= 0; i--)
            if (anc[x][i] != anc[y][i])
                x = anc[x][i], y = anc[y][i];
        return anc[x][0];
    }
} T;
int main()
{
    scanf("%d %d %d", &n, &m, &root);
    T.init(n);
    for (ri i = 1; i <= n - 1; i++)
    {
        scanf("%d %d", &x, &y);
        T.add_edge(x, y);
    }
    T.dfs(root, 0);
    while (m--)
    {
        scanf("%d %d", &x, &y);
        printf("%d\n", T.lca(x, y));
    }
    return 0;
}
