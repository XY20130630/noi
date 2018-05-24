#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') f = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

template <typename Tp> bool chkmax(Tp &x, Tp y) {return x > y ? 0 : (x=y,1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x < y ? 0 : (x=y,1);}
template <typename Tp> Tp Max(Tp x, Tp y) {return x > y ? x : y;}
template <typename Tp> Tp Min(Tp x, Tp y) {return x < y ? x : y;}

const int MAXN = 30010;

int T, n;
char s[MAXN];
int str[MAXN];

typedef unsigned int ULL;

const int MOD = 998244353;

ULL base[MAXN], hs[MAXN];
int base1[MAXN], hs1[MAXN];

void init()
{
	n = strlen(s + 1);
	FOR(i, 1, n) str[i] = s[i] - 'a' + 1;
	base[0] = 1; FOR(i, 1, n) base[i] = base[i - 1] * 233;
	base1[0] = 1; FOR(i, 1, n) base1[i] = 1ll * base1[i - 1] * 233 % MOD;
	FOR(i, 1, n) hs[i] = hs[i - 1] + str[i] * base[i - 1];
	FOR(i, 1, n) hs1[i] = (hs1[i - 1] + 1ll * str[i] * base1[i - 1] % MOD) % MOD;
}

#define same(l1, r1, l2, r2) ({ char f; if ((l1) > (r1) || (l2) > (r2)) f = false;	else if ((l1) < 1 || (l2) < 1 || (r1) > n || (r2) > n) f = false;	else f = (hs[(r1)] - hs[(l1) - 1]) * base[(l2) - (l1)] == hs[(r2)] - hs[(l2) - 1] &&		1ll * (hs1[(r1)] - hs1[(l1) - 1] + MOD) % MOD * base1[(l2) - (l1)] % MOD == (hs1[(r2)] - hs1[(l2) - 1] + MOD) % MOD; f;})

int sum1[MAXN << 2], sum2[MAXN << 2];

void insert1(int now, int l, int r, int x, int y, int z)
{
	//if (l < 1 || r > n) return;
	//if (l > r) return;

	if (x <= l && r <= y) sum1[now] += z;
	else {
		int mid = (l + r) >> 1;
		if (x <= mid) insert1(now << 1, l, mid, x, y, z);
		if (mid < y) insert1(now << 1 | 1, mid + 1, r, x, y, z);
		//sum1[id(l, r)] = sum1[id(l, mid)] + sum1[id(mid + 1, r)];
	}
}

void insert2(int now, int l, int r, int x, int y, int z)
{
	//if (l < 1 || r > n) return;
	//if (l > r) return;

	if (x <= l && r <= y) sum2[now] += z;
	else {
		int mid = (l + r) >> 1;
		if (x <= mid) insert2(now << 1, l, mid, x, y, z);
		if (mid < y) insert2(now << 1 | 1, mid + 1, r, x, y, z);
		//sum2[id(l, r)] = sum2[id(l, mid)] + sum2[id(mid + 1, r)];
	}
}

int query1(int now, int l, int r, int x)
{
	if (l == r) return sum1[now];
	int mid = (l + r) >> 1;
	if (x <= mid) return query1(now << 1, l, mid, x) + sum1[now];
	else return query1(now << 1 | 1, mid + 1, r, x) + sum1[now];
}

int query2(int now, int l, int r, int x)
{
	if (l == r) return sum2[now];
	int mid = (l + r) >> 1;
	if (x <= mid) return query2(now << 1, l, mid, x) + sum2[now];
	else return query2(now << 1 | 1, mid + 1, r, x) + sum2[now];
}

void calc(int lp, int rp, int step)
{
	if (str[lp] != str[rp]) return;
	
	int l, r, lans, rans;

	l = 0; r = step - 1;
	
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (same(lp, lp + mid, rp, rp + mid)) {
			rans = mid; l = mid + 1;
		}
		else r = mid - 1;
	}

	l = 0; r = step - 1;

	while (l <= r) {
		int mid = (l + r) >> 1;
		if (same(lp - mid, lp, rp - mid, rp)) {
			lans = mid; l = mid + 1;
		}
		else r = mid - 1;
	}

	if (lans + rans + 1 >= step)
		insert1(1, 1, n, rp - lans + step - 1, rp + rans, 1);
}

void calc2(int lp, int rp, int step)
{
	if (str[lp] != str[rp]) return;
	
	int l, r, lans, rans;

	l = 0; r = step - 1;
	
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (same(lp, lp + mid, rp, rp + mid)) {
			rans = mid; l = mid + 1;
		}
		else r = mid - 1;
	}

	l = 0; r = step - 1;

	while (l <= r) {
		int mid = (l + r) >> 1;
		if (same(lp - mid, lp, rp - mid, rp)) {
			lans = mid; l = mid + 1;
		}
		else r = mid - 1;
	}

	if (lans + rans + 1 >= step)
		insert2(1, 1, n, lp - lans, lp + rans - step + 1, 1);
}

void solve()
{
	init();
	//build(1, n);

	memset(sum1, 0, sizeof sum1);
	memset(sum2, 0, sizeof sum2);
	
	FOR(i, 1, n / 2)
		for (int j = 1; j <= n; j += i)
			if (j + i <= n) calc(j, j + i, i);
	FOR(i, 1, n / 2)
		for (int j = 1; j <= n; j += i)
			if (j + i <= n) calc2(j, i + j, i);
	LL ans = 0;
	FOR(i, 1, n - 1)
		ans += 1ll * query1(1, 1, n, i) * query2(1, 1, n, i + 1);
	printf("%lld\n", ans);
}

int main()
{
	in(T);

	while (T--) {
		scanf("%s", s + 1); solve();
	}
	
	return 0;
}
