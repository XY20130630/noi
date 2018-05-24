

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
const int MOD1 = 14233333;
const int MOD2 = 1000000009;
const int base = 131;

const int inv2 = 526717562;
const int inv1 = 7388295;

int n, m;
int L[MAXN];
int pre[MAXN], nxt[MAXN];

using std::list;
using std::pair;
using std::make_pair;
list<pair<int, int> >sb[20000010];

int b1[100], b2[100];
int lft[100][2], rgt[100][2];

char s[10000010];

void solve()
{
	int opt; in(opt);

	if (opt == 1) {
		int x, y; in(x); in(y);
		nxt[x] = y; pre[y] = x;

		lft[0][0] = rgt[0][0] = 0;
		FOR(i, 1, 50) {lft[++lft[0][0]][0] = L[x]; if (!pre[x]) break; x = pre[x];}
		FOR(i, 1, 50) {rgt[++rgt[0][0]][0] = L[y]; if (!nxt[y]) break; y = nxt[y];}

		FOR(i, 1, rgt[0][0]) {
			rgt[i][1] = (rgt[i - 1][1] + rgt[i][0] * 1ll * b2[i - 1]) % MOD2;
			if (i != 1) rgt[i][0] = (rgt[i - 1][0] + rgt[i][0] * 1ll * b1[i - 1]) % MOD1;
		}

		FOR(i, 1, lft[0][0]) {
			lft[i][1] = (lft[i - 1][1] * 1ll * base % MOD2 + lft[i][0]) % MOD2;
			if (i != 1) lft[i][0] = (lft[i - 1][0] * 1ll * base % MOD1 + lft[i][0]) % MOD1;
		}

		//puts("WA");
		
		FOR(i, 1, lft[0][0]) FOR(j, 1, Min(50 - i, rgt[0][0])) {
			int a = (lft[i][0] + rgt[j][0] * 1ll * b1[i] % MOD1) % MOD1;
			int b = (lft[i][1] + rgt[j][1] * 1ll * b2[i] % MOD2) % MOD2;
			char flag = false;
			for (auto it = sb[a].begin(); it != sb[a].end(); it++) {
				if (it -> first == b) {
					it -> second++; flag = true; break;
				}
			}
			if (!flag) sb[a].push_back(make_pair(b, 1));
		}
	}

	else if (opt == 2) {
		int x; in(x);
		int y = nxt[x];
		pre[y] = 0; nxt[x] = 0;
		
		lft[0][0] = rgt[0][0] = 0;
		FOR(i, 1, 50) {lft[++lft[0][0]][0] = L[x]; if (!pre[x]) break; x = pre[x];}
		FOR(i, 1, 50) {rgt[++rgt[0][0]][0] = L[y]; if (!nxt[y]) break; y = nxt[y];}

		FOR(i, 1, rgt[0][0]) {
			rgt[i][1] = (rgt[i - 1][1] + rgt[i][0] * 1ll * b2[i - 1]) % MOD2;
			if (i != 1) rgt[i][0] = (rgt[i - 1][0] + rgt[i][0] * 1ll * b1[i - 1]) % MOD1;
		}

		FOR(i, 1, lft[0][0]) {
			lft[i][1] = (lft[i - 1][1] * 1ll * base % MOD2 + lft[i][0]) % MOD2;
			if (i != 1) lft[i][0] = (lft[i - 1][0] * 1ll * base % MOD1 + lft[i][0]) % MOD1;
		}

		FOR(i, 1, lft[0][0]) FOR(j, 1, Min(50 - i, rgt[0][0])) {
			int pos = (lft[i][0] + rgt[j][0] * 1ll * b1[i] % MOD1) % MOD1;
			char flag = false;
			for (auto it = sb[pos].begin(); it != sb[pos].end(); it++) {
				if (it -> first == (lft[i][1] + rgt[j][1] * 1ll * b2[i] % MOD2) % MOD2) {
					it -> second--; if (!it -> second) sb[pos].erase(it); flag = true;
					break;
				}
			}
			assert(flag);
		}
	}

	else {
		scanf("%s", s + 1); int len; in(len);

		const int MOD = 998244353;
		
		int hs1 = 0, hs2 = 0;
		
		FOR(i, 1, len) {
			hs1 = (hs1 + (s[i] - '0' + 1) * 1ll * b1[i - 1] % MOD1) % MOD1;
			hs2 = (hs2 + (s[i] - '0' + 1) * 1ll * b2[i - 1] % MOD2) % MOD2;
		}

		int r = strlen(s + 1), ans = 1;
		
		FOR(i, 1, r - len + 1) {
			int f = 0;
			for (auto it = sb[hs1].begin(); it != sb[hs1].end(); it++)
				if (it -> first == hs2) {
					f = it -> second % MOD;
					break;
				}
			ans = 1ll * ans * f % MOD;
			if (i != r - len + 1) {
				hs1 = (((hs1 - (s[i] - '0' + 1) + MOD1) % MOD1 * 1ll * inv1 % MOD1) + b1[len - 1] * 1ll * (s[i + len] - '0' + 1) % MOD1) % MOD1;
				hs2 = (((hs2 - (s[i] - '0' + 1) + MOD2) % MOD2 * 1ll * inv2 % MOD2) + b2[len - 1] * 1ll * (s[i + len] - '0' + 1) % MOD2) % MOD2;
			}
		}

		printf("%d\n", ans);
	}
}

int main()
{
	in(n); in(m);

	b1[0] = b2[0] = 1;
	FOR(i, 1, 60) b1[i] = b1[i - 1] * 1ll * base % MOD1, b2[i] = b2[i - 1] * 1ll * base % MOD2;
	
	FOR(i, 1, n) {
		in(L[i]), pre[i] = nxt[i] = 0;

		L[i]++;

		char flag = false;
		for (auto it = sb[L[i]].begin(); it != sb[L[i]].end(); it++) {
			if (it -> first == L[i]) {
				it -> second++; flag = true; break;
			}
		}
		if (!flag) sb[L[i]].push_back(make_pair(L[i], 1));
	}

	while (m--) solve();
	
	return 0;
}
