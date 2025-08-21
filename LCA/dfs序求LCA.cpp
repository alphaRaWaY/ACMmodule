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
int n, m, root, x, y;
struct LCA
{
	vector<int> g[N];
    int n, id, root, dfn[N], anc[N][30]; //注意要开log2(n), 需根据题目调整
    
    void init(int _n)
    {
    	/*
    	使用前需要先调用init()函数设置n
    	注意这里复杂度是O(nlogn)
    	*/
        n = _n; id = 0;
        for (ri i = 1; i <= n; i++)
        {
            dfn[i] = 0; g[i].clear();
            for (ri j = 0; j <= __lg(n); j++) anc[i][j] = 0;
        }
    }
    inline int get(int x, int y) { return dfn[x] < dfn[y] ? x : y; }
    void add_edge(int x, int y) { g[x].pb(y); g[y].pb(x); }
    void dfs(int x, int fa)
    {
        anc[dfn[x] = ++id][0] = fa;
        for (auto y : g[x]) if (y != fa) dfs(y, x);
    }
    void rmq()
    {
        for (ri j = 1; j <= __lg(n); j++)
            for (ri i = 1; i + (1 << j) - 1 <= n; i++)
                anc[i][j] = get(anc[i][j - 1], anc[i + (1 << (j - 1))][j - 1]);
    }
    int lca(int x, int y)
    {
        if (x == y) return x;
        if ((x = dfn[x]) > (y = dfn[y])) swap(x, y);
        int d = __lg(y - x++);
        return get(anc[x][d], anc[y - (1 << d) + 1][d]);
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
    T.rmq();
    while (m--)
    {
        scanf("%d %d", &x, &y);
        printf("%d\n", T.lca(x, y));
    }
    return 0;
}
