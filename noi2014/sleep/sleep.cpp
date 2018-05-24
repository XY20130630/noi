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

int n, m;
char opt[MAXN][5];
int t[MAXN];

int check(int pos, int x)
{
	FOR(i, 1, n) {
		if (opt[i][0] == 'A') x &= (t[i] >> (pos - 1) & 1);
		else if (opt[i][0] == 'O') x |= (t[i] >> (pos - 1) & 1);
		else x ^= (t[i] >> (pos - 1) & 1);
	}
	return x;
}

int solve(int pos, char up)
{
	int L = 0, R = (up ? (m >> (pos - 1) & 1) : 1);

	int can = -1, chose = 0;
	FOR(i, L, R) if (chkmax(can, check(pos, i))) chose = i;

	if (pos == 1) return can;
	return (can << (pos - 1)) + solve(pos - 1, up && chose == R);
}

int main()
{
	in(n); in(m);
	FOR(i, 1, n) scanf("%s", opt[i]), in(t[i]);

	printf("%d\n", solve(30, 1));
	
	return 0;
}
