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

int q;
char str[MAXN];

int n, fail[MAXN], dep[MAXN], num[MAXN];

void solve()
{
	scanf("%s", str + 1);
	n = strlen(str + 1);

	fail[1] = 0; dep[1] = 1;

	FOR(i, 2, n) {
		int tmp = fail[i - 1];
		while (str[tmp + 1] != str[i] && tmp) tmp = fail[tmp];

		if (str[tmp + 1] == str[i]) fail[i] = tmp + 1;
		else fail[i] = 0;

		dep[i] = dep[fail[i]] + 1;
	}

	num[1] = 0;
	FOR(i, 2, n) {
		int tmp = num[i - 1];
		while ((str[tmp + 1] != str[i] || (tmp + 1 > i / 2)) && tmp) tmp = fail[tmp];

		if (str[tmp + 1] == str[i] && (tmp + 1 <= i / 2)) num[i] = tmp + 1;
		else num[i] = 0;
	}

	int ans = 1;
	FOR(i, 1, n) ans = 1ll * ans * (dep[num[i]] + 1) % (1000000007);

	printf("%d\n", ans);
}

int main()
{
	in(q); while (q--) solve();
	return 0;
}
