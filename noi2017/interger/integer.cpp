#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

const int MAXN = 1200010;
const int h1 = 0, h2 = 1073741823;

int n;
int seg[MAXN << 2];
char zero[MAXN << 2], one[MAXN << 2];
char tag1[MAXN << 2], tag2[MAXN << 2];

void build(int now, int l, int r)
{
	zero[now] = true;
	one[now] = false;
	tag1[now] = false;
	tag2[now] = false;

	if (l == r) seg[now] = 0;
	else {
		int mid = (l + r) >> 1;
		build(now << 1, l, mid); build(now << 1 | 1, mid + 1, r);
	}
}

char remain;

#define pushdown(now) ({if (tag1[(now)]) {tag2[((now)) << 1] = tag2[(now) << 1 | 1] = false;tag1[(now) << 1] = tag1[(now) << 1 | 1] = true;		one[(now) << 1] = one[(now) << 1 | 1] = false;		zero[(now) << 1] = zero[(now) << 1 | 1] = true;		seg[(now) << 1] = seg[(now) << 1 | 1] = h1;		tag1[(now)] = false;	}		if (tag2[(now)]) {		tag1[(now) << 1] = tag1[(now) << 1 | 1] = false;		tag2[(now) << 1] = tag2[(now) << 1 | 1] = true;		one[(now) << 1] = one[(now) << 1 | 1] = true;		zero[(now) << 1] = zero[(now) << 1 | 1] = false;		seg[(now) << 1] = seg[(now) << 1 | 1] = h2;		tag2[(now)] = false;	} 0;})

void add(int now, int l, int r, int x, int y)
{
	if (l == r) {
		seg[now] += y;
		if (seg[now] > h2) {
			remain = true; seg[now] -= (1 << 30);
		}
		zero[now] = one[now] = false;
		if (seg[now] == 0) zero[now] = true;
		else if (seg[now] == h2) one[now] = true;
		return;
	}
	else {
		pushdown(now);
		int mid = (l + r) >> 1;
		if (x <= mid) add(now << 1, l, mid, x, y);
		else add(now << 1 | 1, mid + 1, r, x, y);
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
	}
}

void remove(int now, int l, int r, int x, int y)
{
	if (l == r) {
		seg[now] -= y;
		if (seg[now] < 0) {
			remain = true; seg[now] += (1 << 30);
		}
		zero[now] = one[now] = false;
		if (seg[now] == 0) zero[now] = true;
		else if (seg[now] == h2) one[now] = true;
		return;
	}
	else {
		pushdown(now);
		int mid = (l + r) >> 1;
		if (x <= mid) remove(now << 1, l, mid, x, y);
		else remove(now << 1 | 1, mid + 1, r, x, y);
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
	}
}

char jinwei(int now, int l, int r, int x, int y)
{
	if (l == r) {
		if (seg[now] == h2) {
			seg[now] = 0;
			zero[now] = one[now] = false;
			if (seg[now] == 0) zero[now] = true;
			else if (seg[now] == h2) one[now] = true;
			return false;
		}
		
		seg[now]++;
//		//assert(seg[now] <= (1 << 30));

		zero[now] = one[now] = false;
		if (seg[now] == 0) zero[now] = true;
		else if (seg[now] == h2) one[now] = true;

		return true;
	}
	pushdown(now);
	if (x <= l && r <= y) {
		int mid = (l + r) >> 1;
		if (one[now << 1]) {
			tag2[now << 1] = false; tag1[now << 1] = true;
			one[now << 1] = false; zero[now << 1] = true;
			seg[now << 1] = h1;
			if (one[now << 1 | 1]) {
				tag2[now << 1 | 1] = false; tag1[now << 1 | 1] = true;
				one[now << 1 | 1] = false; zero[now << 1 | 1] = true;
				seg[now << 1 | 1] = h1;
				zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
				one[now] = (one[now << 1] && one[now << 1 | 1]);
				return false;
			}
			else {
				jinwei(now << 1 | 1, mid + 1, r, x, y);
				zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
				one[now] = (one[now << 1] && one[now << 1 | 1]);
				return true;
			}
		}
		else {
			int ret = jinwei(now << 1, l, mid, x, y);
			zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
			one[now] = (one[now << 1] && one[now << 1 | 1]);
			return ret;
		}
	}
	int mid = (l + r) >> 1;
	if (y <= mid) {
		int ret = jinwei(now << 1, l, mid, x, y);
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
		return ret;
	}
	if (mid < x) {
		int ret = jinwei(now << 1 | 1, mid + 1, r, x, y);
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
		return ret;
	}
	if (jinwei(now << 1, l, mid, x, y)) {
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
		return true;
	}
	int ret = jinwei(now << 1 | 1, mid + 1, r, x, y);
	zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
	one[now] = (one[now << 1] && one[now << 1 | 1]);
	return ret;
}

char jianfa(int now, int l, int r, int x, int y)
{
	if (l == r) {
		//fprintf(stderr, "%d\n", l);
		if (!seg[now]) {
			seg[now] = h2;
			zero[now] = one[now] = false;
			if (seg[now] == 0) zero[now] = true;
			else if (seg[now] == h2) one[now] = true;
			return false;
		}
		seg[now]--;

		if (seg[now] < 0) {
			puts("WA");
		}

		zero[now] = one[now] = false;
		if (seg[now] == 0) zero[now] = true;
		else if (seg[now] == h2) one[now] = true;
		
		return true;
	}
	pushdown(now);
	if (x <= l && r <= y) {
		int mid = (l + r) >> 1;
		if (zero[now << 1]) {
			tag1[now << 1] = false; tag2[now << 1] = true;
			zero[now << 1] = false; one[now << 1] = true;
			seg[now << 1] = h2;
			if (zero[now << 1 | 1]) {
				tag1[now << 1 | 1] = false; tag2[now << 1 | 1] = true;
				zero[now << 1 | 1] = false; one[now << 1 | 1] = true;
				seg[now << 1 | 1] = h2;
				zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
				one[now] = (one[now << 1] && one[now << 1 | 1]);
				return false;
			}
			else {
				jianfa(now << 1 | 1, mid + 1, r, x, y);
				zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
				one[now] = (one[now << 1] && one[now << 1 | 1]);
				return true;
			}
		}
		else {
			int ret = jianfa(now << 1, l, mid, x, y);
			zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
			one[now] = (one[now << 1] && one[now << 1 | 1]);
			return ret;	
		}
	}
	int mid = (l + r) >> 1;
	if (y <= mid) {
		int ret = jianfa(now << 1, l, mid, x, y);
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
		return ret;	
	}
	if (mid < x) {
		int ret = jianfa(now << 1 | 1, mid + 1, r, x, y);
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
		return ret;
	}
	if (jianfa(now << 1, l, mid, x, y)) {
		zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
		one[now] = (one[now << 1] && one[now << 1 | 1]);
		return true;
	}
	int ret = jianfa(now << 1 | 1, mid + 1, r, x, y);
	zero[now] = (zero[now << 1] && zero[now << 1 | 1]);
	one[now] = (one[now << 1] && one[now << 1 | 1]);
	return ret;
}

int query(int now, int l, int r, int x, int y)
{
	if (l == r) return seg[now] >> y & 1;
	pushdown(now);
	int mid = (l + r) >> 1;
	if (x <= mid) return query(now << 1, l, mid, x, y);
	else return query(now << 1 | 1, mid + 1, r, x, y);
}

void solve()
{
	int opt; in(opt);

	if (opt == 1) {
		int x, y; in(x); in(y);
		if (!x) return;
		if (x > 0) {
			//FOR(i, 0, 29) if (x >> i & 1) {
			remain = false;
			add(1, 1, n + 4, (y) / 30 + 1, (x & ((1 << (((y / 30) + 1) * 30 - 1 - y + 1)) - 1)) << ((y - (y / 30 * 30))));
			if (remain) {
				jinwei(1, 1, n + 4, (y) / 30 + 2, n + 4);
			}
			if (y % 30 != 0) {
				remain = false;
				add(1, 1, n + 4, (y) / 30 + 2, x >> (((((y / 30) + 1) * 30 - 1 - y + 1))));
				if (remain) {
					jinwei(1, 1, n + 4, (y) / 30 + 3, n + 4);
				}
			}
				//}
		}
		else {
			remain = false;
			remove(1, 1, n + 4, (y) / 30 + 1, ((-x) & ((1 << (((y / 30) + 1) * 30 - 1 - y + 1)) - 1)) << ((y - (y / 30 * 30))));
			if (remain) {
				jianfa(1, 1, n + 4, (y) / 30 + 2, n + 4);
			}
			if (y % 30 != 0) {
				remain = false;
				remove(1, 1, n + 4, (y) / 30 + 2, (-x) >> (((((y / 30) + 1) * 30 - 1 - y + 1))));
				if (remain) {
					jianfa(1, 1, n + 4, (y) / 30 + 3, n + 4);
				}
			}
		}
	}
	else {
		int x; in(x);
		printf("%d\n", query(1, 1, n + 4, x / 30 + 1, x % 30));
	}
}

int main()
{
	in(n); {int a; in(a); in(a); in(a);}

	build(1, 1, n + 4);
	int q = n; while (q--) solve();
	
	return 0;
}
