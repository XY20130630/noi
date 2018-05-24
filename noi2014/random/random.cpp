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

const int MAXN = 5010;

int x0, a, b, c, d;

int n, m, q;
int p[MAXN * MAXN];
int pos[MAXN * MAXN];
char vis[MAXN][MAXN];

int f(int x) {return (a * 1ll * x % d * x % d + b * 1ll * x % d + c) % d;}

void bfsLD(int x, int y)
{
	if (x > n || y < 1 || vis[x][y]) return;
	vis[x][y] = true;
	bfsLD(x + 1, y); bfsLD(x, y - 1);
}

void bfsUR(int x, int y)
{
	if (x < 1 || y > m || vis[x][y]) return;
	vis[x][y] = true;
	bfsUR(x - 1, y); bfsUR(x, y + 1);
}

int main()
{
	in(x0); in(a); in(b); in(c); in(d);

	in(n); in(m); in(q);
	//FOR(i, 1, n) FOR(j, 1, m) pos[(i - 1) * m + j][0] = i, pos[(i - 1) * m + j][1] = j;

	FOR(i, 1, n * m) p[i] = i;
	
	int x = x0;
	FOR(i, 1, n * m) {
		x = f(x);
		std::swap(p[x % i + 1], p[i]);
	}

	FOR(i, 1, q) {int x, y; in(x); in(y); std::swap(p[x], p[y]);}
	
	FOR(i, 1, n) FOR(j, 1, m)
		pos[p[(i - 1) * m + j]] = (i - 1) * m + j;

	FOR(i, 1, n * m) {
		if (!vis[(pos[i] - 1) / m + 1][(pos[i] - 1) % m + 1]) {
			printf("%d ", i);
			bfsLD((pos[i] - 1) / m + 2, (pos[i] - 1) % m);
			bfsUR((pos[i] - 1) / m    , (pos[i] - 1) % m + 2);
		}
	}

	putchar(10);
	
	return 0;
}

