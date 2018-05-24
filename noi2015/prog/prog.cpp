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

const int MAXN = 1000010;

int T;
int fa[MAXN];
int edge[MAXN][3];

using std::map;
map<int, int>M;

int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

void solve()
{
	int n; in(n);
	FOR(i, 1, 2 * n) fa[i] = i;

	M.clear();

	int tot = 0;
	
	FOR(i, 1, n) {
		in(edge[i][0]); in(edge[i][1]); in(edge[i][2]);

		int x = edge[i][0], y = edge[i][1], z = edge[i][2];

		if (M.count(x)) x = M[x]; else x = M[x] = ++tot;
		if (M.count(y)) y = M[y]; else y = M[y] = ++tot;
		
		if (z) fa[find(x)] = find(y);
	}

	FOR(i, 1, n) {
		int x = edge[i][0], y = edge[i][1], z = edge[i][2];

		if (M.count(x)) x = M[x]; else x = M[x] = ++tot;
		if (M.count(y)) y = M[y]; else y = M[y] = ++tot;
		
		if (!z) if (find(x) == find(y)) {puts("NO"); return;}
	}

	puts("YES");
}

int main()
{
	in(T);
	while (T--) solve();
	return 0;
}
