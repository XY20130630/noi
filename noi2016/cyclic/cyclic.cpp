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

int n, m, k;

using std::map;
using std::pair;
using std::make_pair;

map<pair<int, int>, LL>M1;
map<pair<int, int>, LL>M2;

const int MAXN = 1000010;
const int Limit = 1000000;

int p[MAXN], cnt;
LL mu[MAXN], prime[MAXN];
char no_prime[MAXN];

map<int, LL>sM;

void get_prime()
{
	mu[1] = 1;
	FOR(i, 2, Limit) {
		if (!no_prime[i]) {
			prime[++prime[0]] = i; mu[i] = -1;
		}
		for (int j = 1; prime[j] * i <= Limit; j++) {
			no_prime[prime[j] * i] = true;
			if (i % prime[j] == 0) break;
			mu[prime[j] * i] = -mu[i];
		}
		mu[i] += mu[i - 1];
	}
}

LL get_M(LL x)
{
	if (!x) return 0;
	if (x <= Limit) return mu[x];
	if (sM.count(x)) return sM[x];
	LL ret = 1;
	for (LL i = 2, j; i <= x; i = j + 1) {
		j = x / (x / i);
		ret -= get_M(x / j) * (j - i + 1);
	}
	return sM[x] = ret;
}

LL solve1(LL x, LL num)
{
	//1
	if (!x) return 0;
	if (!num) return x;
	if (M1.count(make_pair(x, num))) return M1[make_pair(x, num)];
	return M1[make_pair(x, num)] = solve1(x, num - 1) - solve1(x / p[num], num - 1);
}

LL solve2(LL x, LL num)
{
	//mu
	if (!x) return 0;
	if (!num) return get_M(x);
	if (M2.count(make_pair(x, num))) return M2[make_pair(x, num)];
	return M2[make_pair(x, num)] = solve2(x, num - 1) + solve2(x / p[num], num);
}

void divide(int x)
{
	int sqr = sqrt(x);
	for (int i = 2; i <= sqr; i++) {
		if (x % i == 0) p[++cnt] = i;
		while (x % i == 0) x /= i;
	}
	if (x != 1) p[++cnt] = x;
}

int main()
{
	in(n); in(m); in(k);

	divide(k);
	int min = Min(n, m);

	LL ans = 0;

	get_prime();

	for (LL i = 1, j; i <= min; i = j + 1) {
		j = Min(n / (n / i), m / (m / i));
		LL two = solve1(m / i, cnt);
		LL one = solve2(j, cnt) - solve2(i - 1, cnt);
		ans += one * two * (n / i);
	}

	printf("%lld\n", ans);
	
	return 0;
}

