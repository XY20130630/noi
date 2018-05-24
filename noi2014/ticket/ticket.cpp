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

const int MAXN = 200010;

int n;
int fa[MAXN];
int head[MAXN], data[MAXN], nxt[MAXN], cnt;
int top[MAXN], sz[MAXN], id[MAXN], dep[MAXN], pre[MAXN];
int anc[MAXN][18];

char calced[MAXN << 2];
int *tu[MAXN << 2], num[MAXN << 2], tmp[MAXN << 2];
LL s[MAXN], p[MAXN], q[MAXN], L[MAXN], f[MAXN];

struct Pt {
	LL x, y;
	Pt(LL a=0, LL b=0) {x = a, y = b;}
	Pt operator - (const Pt &another) {return Pt(x - another.x, y - another.y);}
};

void add(int x, int y) {nxt[cnt] = head[x]; data[cnt] = y; head[x] = cnt++;}

void dfs1(int now, int pa)
{
	sz[now] = 1;
	dep[now] = dep[pa] + 1;
	s[now] += s[pa];

	anc[now][0] = pa;
	FOR(i, 1, 17) anc[now][i] = anc[anc[now][i - 1]][i - 1];

	for (int i = head[now]; i != -1; i = nxt[i])
		dfs1(data[i], now), sz[now] += sz[data[i]];
}

void dfs2(int now)
{
	id[now] = ++id[0]; pre[id[0]] = now;

	int son = 0;
	for (int i = head[now]; i != -1; i = nxt[i])
		if (sz[data[i]] > sz[son]) son = data[i];

	if (son) top[son] = top[now], dfs2(son);

	for (int i = head[now]; i != -1; i = nxt[i])
		if (data[i] != son) top[data[i]] = data[i], dfs2(data[i]);
}

char cmp(const int &x, const int &y)
{
	return s[pre[x]] < s[pre[y]];
}

char cross(const Pt &x, const Pt &y)
{
	char flag = 1;
	if (x.y < 0) flag = -flag;
	if (y.y < 0) flag = -flag;
	if (flag == 1) return 1.0 * x.x / x.y >= 1.0 * y.x / y.y;
	else return 1.0 * x.x / x.y <= 1.0 * y.x / y.y;
}

char check(int now, LL x, LL y)
{
	int a = tu[now][num[now] - 1];
	int b = tu[now][num[now]];
	return cross(Pt(x, y) - Pt(s[a], f[a]), Pt(s[b], f[b]) - Pt(s[a], f[a]));
}

void make_tu(int now, int l, int r)
{
	int tot = 0;
	FOR(i, l, r)
		tmp[++tot] = pre[i], assert(i == l || s[pre[i]] > s[pre[i - 1]]);
	FOR(i, 1, tot) {
		while (num[now] > 1 && check(now, s[tmp[i]], f[tmp[i]])) num[now]--;
		tu[now][++num[now]] = tmp[i];
	}
}

LL __query(int i, int now)
{
	int l = 1, r = num[now];
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (mid != r && p[i] * (s[tu[now][mid + 1]] - s[tu[now][mid]]) > f[tu[now][mid + 1]] - f[tu[now][mid]])
			l = mid + 1;
		else if (mid != l && p[i] * (s[tu[now][mid]] - s[tu[now][mid - 1]]) < f[tu[now][mid]] - f[tu[now][mid - 1]])
			r = mid - 1;
		else {
			return f[tu[now][mid]] - s[tu[now][mid]] * p[i];
		}
	}
	assert(0);
}

LL _query(int now, int l, int r, int x, int y, int qry)
{
	if (x <= l && r <= y) {
		if (!calced[now]) make_tu(now, l, r), calced[now] = true;
		return __query(qry, now);
	}
	int mid = (l + r) >> 1;
	if (y <= mid) return _query(now << 1, l, mid, x, y, qry);
	if (mid < x) return _query(now << 1 | 1, mid + 1, r, x, y, qry);
	return Min(_query(now << 1, l, mid, x, y, qry), _query(now << 1 | 1, mid + 1, r, x, y, qry));
}

LL query(int now, int x, int y)
{
	LL ret = 0x3f3f3f3f3f3f3f3fLL;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) x ^= y ^= x ^= y;
		chkmin(ret, _query(1, 1, n, id[top[x]], id[x], now));
		x = fa[top[x]];
	}
	if (dep[x] < dep[y]) x ^= y ^= x ^= y;
	chkmin(ret, _query(1, 1, n, id[y], id[x], now));
	assert(ret != 0x3f3f3f3f3f3f3f3fLL);
	return ret;
}

void dp(int now)
{
	if (now == 1) f[now] = 0;
	else {
		int up = now;
		DNF(i, 17, 0) if (anc[up][i] && s[now] - s[anc[up][i]] <= L[now]) up = anc[up][i];
		assert(up != now);
		f[now] = query(now, fa[now], up) + q[now] + s[now] * p[now];
	}
	for (int i = head[now]; i != -1; i = nxt[i]) dp(data[i]);
}

void build(int now, int l, int r)
{
	tu[now] = new int[r - l + 1];
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(now << 1, l, mid); build(now << 1 | 1, mid + 1, r);
}

int main()
{
	in(n); {int t; in(t);}
	memset(head, -1, sizeof head);
	
	FOR(i, 2, n) {
		in(fa[i]), in(s[i]), in(p[i]), in(q[i]), in(L[i]), add(fa[i], i);
	}
	
	dfs1(1, 0);
	top[1] = 1; dfs2(1);

	build(1, 1, n); dp(1);
	FOR(i, 2, n) printf("%lld\n", f[i]);

	return 0;
}
