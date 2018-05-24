#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') ch = getchar(), f = -1;
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

template <typename Tp> void out(Tp x) {
	if (x > 9) out(x / 10);
	putchar(x % 10 + '0');
	return;
}

template <typename Tp> Tp Max(const Tp &x, const Tp &y) {return x > y ? x : y;}
template <typename Tp> Tp Min(const Tp &x, const Tp &y) {return x < y ? x : y;}
template <typename Tp> bool chkmax(Tp &x, Tp y) {return x >= y ? 0 : (x=y, 1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x <= y ? 0 : (x=y, 1);}

const int MAXN = 100010;

int n, fa[MAXN];
int head[MAXN], data[MAXN << 1], nxt[MAXN << 1], cnt;

int sum[MAXN << 2], tag[MAXN << 2];

void add(int x, int y)
{
	nxt[cnt] = head[x]; data[cnt] = y; head[x] = cnt++;
}

int top[MAXN], depth[MAXN], id[MAXN], sz[MAXN], ed[MAXN];

void dfs(int now, int pa)
{
	sz[now] = 1;
	depth[now] = depth[pa] + 1;
	for (int i = head[now]; i != -1; i = nxt[i]) {
		if (data[i] == pa) continue;
		dfs(data[i], now); sz[now] += sz[data[i]];
	}
}

void dfs2(int now, int pa)
{
	int son = 0;
	id[now] = ++id[0];
	for (int i = head[now]; i != -1; i = nxt[i])
		if (data[i] != pa && sz[data[i]] > sz[son]) son = data[i];
	if (son) top[son] = top[now], dfs2(son, now);
	for (int i = head[now]; i != -1; i = nxt[i])
		if (data[i] != pa && data[i] != son)
			top[data[i]] = data[i], dfs2(data[i], now);
	ed[now] = id[0];
}

void pushdown(int now, int l, int r)
{
	if (tag[now] != -1) {
		int mid = (l + r) >> 1;
		sum[now << 1] = (mid - l + 1) * tag[now];
		sum[now << 1 | 1] = (r - mid) * tag[now];
		tag[now << 1] = tag[now << 1 | 1] = tag[now];
		tag[now] = -1;
	}
}

void modify(int now, int l, int r, int x, int y, int z)
{
	if (x <= l && r <= y) {
		sum[now] = (r - l + 1) * z; tag[now] = z;
		return;
	}
	pushdown(now, l, r);
	int mid = (l + r) >> 1;
	if (x <= mid) modify(now << 1, l, mid, x, y, z);
	if (mid < y) modify(now << 1 | 1, mid + 1, r, x, y, z);
	sum[now] = sum[now << 1] + sum[now << 1 | 1];
}

int query(int now, int l, int r, int x, int y)
{
	if (x <= l && r <= y) return sum[now];
	pushdown(now, l, r);
	int mid = (l + r) >> 1, ret = 0;
	if (x <= mid) ret += query(now << 1, l, mid, x, y);
	if (mid < y) ret += query(now << 1 | 1, mid + 1, r, x, y);
	return ret;
}

void solve()
{
	int q; in(q);
	char opt[10];
	
	while (q--) {
		scanf("%s", opt);
		if (opt[0] == 'i') {
			int x; in(x); x++;
			if (query(1, 1, n, id[x], id[x]) == 1) {puts("0"); continue;}
			int need = 0;
			while (top[x] != 1) {
				need += depth[x] - depth[top[x]] + 1 - query(1, 1, n, id[top[x]], id[x]);
				modify(1, 1, n, id[top[x]], id[x], 1);
				x = fa[top[x]];
			}
			need += depth[x] - query(1, 1, n, 1, id[x]);
			modify(1, 1, n, 1, id[x], 1);
			printf("%d\n", need);
		}
		else {
			int x; in(x); x++;
			if (query(1, 1, n, id[x], id[x]) == 0) {puts("0"); continue;}
			printf("%d\n", query(1, 1, n, id[x], ed[x]));
			modify(1, 1, n, id[x], ed[x], 0);
		}
	}
}

int main()
{
	in(n);
	memset(tag, -1, sizeof tag);
	memset(head, -1, sizeof head);
	FOR(i, 2, n) in(fa[i]), fa[i]++, add(fa[i], i);
	dfs(1, 0); top[1] = 1; dfs2(1, 0);
	solve();
	return 0;
}
