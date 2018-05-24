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

const int MAXN = 300010;

int n, A[MAXN];
int sa[MAXN], height[MAXN], rnk[MAXN], c[MAXN], c1[MAXN], c2[MAXN];

char str[MAXN];

void get_height()
{
	FOR(i, 1, n) rnk[sa[i]] = i;
	FOR(i, 1, n) {
		if (rnk[i] == 1) continue;
		int &now = height[rnk[i]];
		now = Max(height[rnk[i - 1]] - 1, 0);
		while (str[sa[rnk[i]] + now] == str[sa[rnk[i] - 1] + now]) now++;
	}
}

void build_sa()
{
	int *x = c1, *y = c2, m = 26;

	FOR(i, 1, n) c[x[i] = str[i] - 'a' + 1]++;
	FOR(i, 1, m) c[i] += c[i - 1];
	DNF(i, n, 1) sa[c[x[i]]--] = i;

	for (int p = 1; p <= n; p <<= 1) {
		int t = 0;
		FOR(i, n - p + 1, n) y[++t] = i;
		FOR(i, 1, n) if (sa[i] > p) y[++t] = sa[i] - p;

		FOR(i, 0, m) c[i] = 0;
		FOR(i, 1, n) c[x[y[i]]]++;
		FOR(i, 1, m) c[i] += c[i - 1];
		DNF(i, n, 1) sa[c[x[y[i]]]--] = y[i];

		std::swap(x, y);
		m = x[sa[1]] = 1;

		FOR(i, 2, n)
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + p] == y[sa[i - 1] + p])
				x[sa[i]] = m;
			else
				x[sa[i]] = ++m;

		if (m >= n) return;
	}
}

int to[MAXN], fa[MAXN], mx[MAXN], sz[MAXN], mi[MAXN];
char cmp(const int &x, const int &y) {return height[x + 1] > height[y + 1];}

LL ans1[MAXN];
LL ans2[MAXN];

int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

int main()
{
	in(n);
	scanf("%s", str + 1);

	FOR(i, 1, n) in(A[i]);

	build_sa(); get_height();

	FOR(i, 1, n - 1) to[i] = i;
	std::sort(to + 1, to + n, cmp);

	FOR(i, 1, n) fa[i] = i, mx[i] = A[sa[i]], mi[i] = A[sa[i]], sz[i] = 1;

	memset(ans2, 0xc0, sizeof ans2); LL inf = ans2[0];
	
	FOR(i, 1, n - 1) {
		int x = find(to[i]), y = find(to[i] + 1);
		int can = height[to[i] + 1];
		ans1[can] += sz[x] * 1ll * sz[y];
		chkmax(ans2[can], mx[x] * 1ll * mx[y]);
		chkmax(ans2[can], mi[x] * 1ll * mi[y]);
		chkmin(mi[x], mi[y]); chkmax(mx[x], mx[y]);
		sz[x] += sz[y]; fa[y] = x;
	}

	DNF(i, n - 1, 0) ans1[i] += ans1[i + 1], chkmax(ans2[i], ans2[i + 1]);
	FOR(i, 0, n - 1) printf("%lld %lld\n", ans1[i], ans2[i] == inf ? 0 : ans2[i]);

	return 0;
}
