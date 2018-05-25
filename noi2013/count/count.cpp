#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define DNF(i, a, b) for (int i = (a); i >= (b); i--)

template <typename Tp> void out(Tp x) {
	if (x > 9) out(x / 10);
	putchar(x % 10 + '0');
	return;
}

template <typename Tp> Tp Max(const Tp &x, const Tp &y) {return x > y ? x : y;}
template <typename Tp> Tp Min(const Tp &x, const Tp &y) {return x < y ? x : y;}
#define chkmax(x, y) ((x) >= (y) ? 0 : (x=(y), 1))
#define chkmin(x, y) ((x) <= (y) ? 0 : (x=(y), 1))

#define getchar() (*S++)

char BB[1 << 26], *S = BB;

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') ch = getchar(), f = -1;
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

const int MAXN = 200010;

int n;
int inp[MAXN], tur[MAXN], dfn[MAXN], bfn[MAXN], min[MAXN], max[MAXN];

int main()
{
	fread(BB, 1, 1 << 26, stdin);
	
	in(n);
	FOR(i, 1, n) in(inp[i]);
	FOR(i, 1, n) in(bfn[i]);
	FOR(i, 1, n) tur[inp[i]] = i;
	FOR(i, 1, n) dfn[i] = tur[bfn[i]];

	int minx = n + 1;
	int maxx = 0;

	min[n + 1] = minx;
	
	DNF(i, n, 1) {
		chkmin(minx, dfn[i]), min[i] = minx;
		chkmax(maxx, dfn[i]), max[i] = maxx;
	}

	double ans = 2;

	FOR(i, 3, n) {
		if (dfn[i] < dfn[i - 1]) ans++;
		else if (max[i - 1] - dfn[i - 1] == n - i + 1 && dfn[i] == dfn[i - 1] + 1 && min[i + 1] > dfn[i]) ans += 0.5;
	}

	printf("%.3lf\n", ans);
	
	return 0;
}
