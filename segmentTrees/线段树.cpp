#include<bits/stdc++.h>
#define ri int
#define f first
#define s second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 1e5 + 10;
int n, m, op, l, r, k, a[N];
struct Tree
{
	/*
	线段树区间加, 区间和模板
	若要求不同，则根据相应要求修改pushup, f, pushdown, update, query等函数
	主要是修改变量c和tag, 或新增变量
	*/
	struct Node
	{
		int c, tag;
	};
	Node tr[4 * N];
	
	void init()
	{
		/*
		需要根据Node结构体的类型, 题目要求进行更改
		时间复杂度为O(n), 多测谨慎调用
		*/
		memset(tr, 0, sizeof(tr));
	}
	inline void pushup(int now)
	{
		tr[now].c = tr[now << 1].c + tr[now << 1 | 1].c;
	}
	inline void f(int now, int l, int r, int k)
	{
		tr[now].tag += k;
		tr[now].c += k * (r - l + 1);
	}
	inline void pushdown(int now, int l, int r)
	{
		if(l == r) return;
		ll mid = (l + r) >> 1;
		f(now << 1, l, mid, tr[now].tag);
		f(now << 1 | 1, mid + 1, r, tr[now].tag);
		tr[now].tag = 0;
	}
	void build(int now, int l, int r)
	{
		if(l == r)
		{
			tr[now].c = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(now << 1, l, mid), build(now << 1 | 1, mid + 1, r);
		pushup(now);
	}
	void update(int ul, int ur, int k, int now, int l, int r)
	{
		if(ul <= l && r <= ur)
		{
			tr[now].tag += k;
			tr[now].c += k * (r - l + 1);
			return;
		}
		if(tr[now].tag) pushdown(now, l, r);
		int mid = (l + r) >> 1;
		if(ul <= mid) update(ul, ur, k, now << 1, l, mid);
		if(ur > mid) update(ul, ur, k, now << 1 | 1, mid + 1, r);
		pushup(now);
	}
	int query(int ql, int qr, int now, int l, int r)
	{
		if(ql <= l && r <= qr) return tr[now].c;
		if(tr[now].tag) pushdown(now, l, r);
		int mid = (l + r) >> 1, res = 0;
		if(ql <= mid) res += query(ql, qr, now << 1, l, mid);
		if(qr > mid) res += query(ql, qr, now << 1 | 1, mid + 1, r);
		return res;
	}
} T;
int main()
{
	/*
	以下为使用示例: 
	scanf("%d %d", &n, &m);
	for(ri i = 1; i <= n; i++) scanf("%d", &a[i]);
	T.build(1, 1, n);
	for(ri i = 1; i <= m; i++)
	{
		scanf("%d", &op);
		if(op == 1) scanf("%d %d %d", &l, &r, &k), T.update(l, r, k, 1, 1, n);
		else scanf("%d %d", &l, &r), printf("%d\n", T.query(l, r, 1, 1, n));
	}
	*/
	return 0;
}