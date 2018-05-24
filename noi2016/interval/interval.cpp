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

struct Int {int l, r;};

int n, m;
Int inter[MAXN];

int all[MAXN];
int max[MAXN << 2], tag[MAXN << 2];

char cmp(const Int &x, const Int &y) {return all[x.r] - all[x.l] < all[y.r] - all[y.l];}

void pushdown(int now)
{
	if (tag[now]) {
		tag[now << 1] += tag[now]; max[now << 1] += tag[now];
		tag[now << 1 | 1] += tag[now]; max[now << 1 | 1] += tag[now];
		tag[now] = 0;
	}
}

void add(int now, int l, int r, int x, int y, int z)
{
	if (x <= l && r <= y) {
		tag[now] += z; max[now] += z; return;
	}
	pushdown(now);
	int mid = (l + r) >> 1;
	if (x <= mid) add(now << 1, l, mid, x, y, z);
	if (mid < y) add(now << 1 | 1, mid + 1, r, x, y, z);
	max[now] = Max(max[now << 1], max[now << 1 | 1]);
}

int main()
{
	in(n); in(m);

	int tot = 0;
	FOR(i, 1, n) {
		in(inter[i].l), in(inter[i].r);
		all[++tot] = inter[i].l; all[++tot] = inter[i].r;
	}
	
	std::sort(all + 1, all + tot + 1);
	tot = std::unique(all + 1, all + tot + 1) - all - 1;

	FOR(i, 1, n) {
		inter[i].l = std::lower_bound(all + 1, all + tot + 1, inter[i].l) - all,
		inter[i].r = std::lower_bound(all + 1, all + tot + 1, inter[i].r) - all;
	}

	std::sort(inter + 1, inter + n + 1, cmp);

	int r = 0, ans = 0x3f3f3f3f;
	
	FOR(l, 1, n) {
		if (l != 1) add(1, 1, tot, inter[l - 1].l, inter[l - 1].r, -1);
		while (r < n && max[1] < m)
			add(1, 1, tot, inter[r + 1].l, inter[r + 1].r, 1), r++;
		if (max[1] < m) break;
		chkmin(ans, all[inter[r].r] - all[inter[r].l] - all[inter[l].r] + all[inter[l].l]);
	}

	printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);

	return 0;
}
