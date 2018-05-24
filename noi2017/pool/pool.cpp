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

const int MOD = 998244353;

int n, s, p;

int power(int x, int y)
{
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1ll * ret * x % MOD;
		x = 1ll * x * x % MOD;
		y >>= 1;
	}
	return ret;
}

const int MAXN = 2010;

int g[MAXN][MAXN];
int f[MAXN][MAXN];

int h[MAXN], a[MAXN], b[MAXN], c[MAXN], t[MAXN];

int calc()
{
	if (!s) return power(p, n);
	
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	memset(b, 0, sizeof b);
	memset(c, 0, sizeof c);

	FOR(i, 1, s) f[1][i] = p;
	DNF(i, s, 1) g[1][i] = (g[1][i + 1] + f[1][i] * 1ll * power(MOD + 1 - p, i) % MOD) % MOD;
	FOR(i, 1, 1001) f[0][i] = 1;

	FOR(i, 2, s) {
		FOR(j, 1, s / i) {
			f[i][j] = (f[i][j] + p * 1ll * power(power(MOD + 1 - p, (i - 1) * j), MOD - 2) % MOD * g[i - 1][j] % MOD) % MOD;
			f[i][j] = (f[i][j] + p * 1ll * power(power(MOD + 1 - p, (i - 1) * j), MOD - 2) % MOD * g[i - 1][j + 1] % MOD) % MOD;
			FOR(k, 2, i - 1) {
				f[i][j] = (f[i][j] + p * 1ll * power(power(MOD + 1 - p, (k - 1) * j), MOD - 2) % MOD * g[k - 1][j + 1] % MOD * power(power(MOD + 1 - p, (i - k) * j), MOD - 2) % MOD * g[i - k][j] % MOD) % MOD;
			}
		}
		DNF(j, s / i, 1)
			g[i][j] = (g[i][j + 1] + f[i][j] * 1ll * power(MOD + 1 - p, i * j) % MOD) % MOD;
	}

	h[0] = 1;
	FOR(i, 1, s) {
		h[i] = p * 1ll * h[i - 1] % MOD;
		FOR(j, 1, i - 1)
			h[i] = (h[i] + 1ll * p * 1ll * h[i - j - 1] % MOD * g[j][1] % MOD) % MOD;
		h[i] = (h[i] + g[i][1]) % MOD;
	}

	g[0][1] = 1;
	
	FOR(i, s + 1, 2 * s) {
		FOR(j, 1, s + 1) h[i] = (h[i] + 1ll * p * h[i - j] % MOD * g[j - 1][1] % MOD) % MOD;
	}

	if (s < n) {
		FOR(i, 0, s) a[i] = p * 1ll * g[i][1] % MOD;

		int y = n - s;

		b[0] = 1; c[1] = 1;
		
		while (y) {
			if (y & 1) {
				memset(t, 0, sizeof t);
				
				FOR(i, 0, s) FOR(j, 0, s)
					t[i + j] = (t[i + j] + 1ll * b[i] * c[j] % MOD) % MOD;
				
				DNF(i, 2 * s, s + 1) FOR(j, 0, s) {
					t[i - (s + 1) + j] = (t[i - (s + 1) + j] + a[s - j] * 1ll * t[i] % MOD) % MOD;
				}
				
				FOR(i, 0, s) b[i] = t[i];
			}

			memset(t, 0, sizeof t);
			
			FOR(i, 0, s) FOR(j, 0, s)
				t[i + j] = (t[i + j] + 1ll * c[i] * c[j] % MOD) % MOD;
			
			DNF(i, 2 * s, s + 1) FOR(j, 0, s) {
				t[i - (s + 1) + j] = (t[i - (s + 1) + j] + a[s - j] * 1ll * t[i] % MOD) % MOD;
			}
			
			FOR(i, 0, s) c[i] = t[i];
			
			y >>= 1;
		}
		//g[0][1] = 1;
		//FOR(i, Min(n, s) + 1, n) {
		//FOR(j, 1, s + 1) h[i] = (h[i] + 1ll * p * h[i - j] % MOD * g[j - 1][1] % MOD) % MOD;
		//}

		int ret = 0;
		FOR(i, 0, s) ret = (ret + b[i] * 1ll * h[i + s] % MOD) % MOD;
		return ret;
	}

	else return h[n];
}

int main()
{
	in(n); in(s);
	int x, y; in(x); in(y); x = y - x;
	p = x * 1ll * power(y, MOD - 2) % MOD;

	//printf("%d\n", calc()); return 0;
	int ans = calc(); s--; ans = (ans - calc() + MOD) % MOD;

	printf("%d\n", ans);
	
	return 0;
}
