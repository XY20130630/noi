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

const int MOD = 1423333;

const int MAXN = 100010;

int T, n, m, c;

using std::vector;
using std::pair;
using std::make_pair;

int fir[MOD + 1], fir2[MOD + 1], fir3[MOD + 1];
vector<pair<pair<int, int>, int> >V[MOD + 1];
vector<pair<pair<int, int>, int> >V2[MOD + 1];

int fx[MAXN], fy[MAXN];

int id(int x, int y)
{
	if (x < 1 || x > n || y < 1 || y > m) return -1;
	int pos = ((x - 1) * 1ll * m + y) % MOD;
	if (fir[pos] != T) return -1;
	FOR(i, 0, V[pos].size() - 1) if (V[pos][i].first.first == x && V[pos][i].first.second == y) return V[pos][i].second;
	return -1;
}

int id2(int x, int y, int now)
{
	if (x < 1 || x > n || y < 1 || y > m) return -1;
	int pos = ((x - 1) * 1ll * m + y) % MOD;
	if (fir2[pos] != T || fir3[pos] != now) return -1;
	FOR(i, 0, V2[pos].size() - 1) if (V2[pos][i].first.first == x && V2[pos][i].first.second == y) return V2[pos][i].second;
	return -1;
}

int abs(int x) {return x < 0 ? -x : x;}

char check()
{
	assert(n * 1ll * m - c == 2);

	int a0, b0, a1, b1;
	FOR(i, 1, n) FOR(j, 1, m) if (id(i, j) == -1) {a0 = i; b0 = j; goto first;}
  first:
	FOR(i, a0, n) FOR(j, 1, m) {
		if (a0 == i && j <= b0) continue;
		if (id(i, j) == -1) {a1 = i; b1 = j; goto second;}
	}

  second:
	return a0 == a1 && abs(b0 - b1) == 1 || b0 == b1 && abs(a0 - a1) == 1;
}

char vis[MAXN];

int st;
pair<int, int>F[MAXN * 8];
pair<int, int>G[MAXN * 24];

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1, 0, 1, 2, 2, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2, -1},
	dy[] = {1, -1, 0, 0, -1, 1, 1, -1, 2, 2, 2, 1, 0, -1, -2, -2, -2, -2, -2, -1, 0, 1, 2, 2};

void dfs(int now)
{
	vis[now] = true;
	int x = fx[now], y = fy[now];
	
	FOR(i, 0, 7) {
		int nxt = id(x + dx[i], y + dy[i]);
		if (nxt == -1) {if (x + dx[i] >= 1 && x + dx[i] <= n && y + dy[i] >= 1 && y + dy[i] <= m) F[++st] = make_pair(x + dx[i], y + dy[i]);}
		else if (!vis[nxt]) dfs(nxt);
	}
}

int fa[MAXN];

int find(int x) {while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;}

char solve(int now)
{
	st = 0; dfs(now);
	std::sort(F + 1, F + st + 1);
	st = std::unique(F + 1, F + st + 1) - F - 1;

	FOR(i, 1, st) {
		int x = F[i].first, y = F[i].second;
		int pos = ((x - 1) * 1ll * m + y) % MOD;
		if (fir2[pos] != T || fir3[pos] != now) {fir2[pos] = T; fir3[pos] = now; V2[pos].clear();}
		V2[pos].push_back(make_pair(make_pair(x, y), i));
	}
	
	FOR(i, 1, st) fa[i] = i;
	FOR(i, 1, st) FOR(j, 0, 3) {
		int nxt = id2(F[i].first + dx[j], F[i].second + dy[j], now);
		if (nxt != -1) fa[find(i)] = find(nxt);
	}

	int block = 0;
	FOR(i, 1, st) if (find(i) == i) block++;

	return block <= 1;
}

char check2()
{
	FOR(i, 1, c) vis[i] = false;
	FOR(i, 1, c) if (!vis[i]) if (!solve(i)) return false;
	return true;
}

int Index;
int dfn[MAXN * 24], low[MAXN * 24];
char ge[MAXN * 24];

void tarjan(int now, int pa)
{
	dfn[now] = low[now] = ++Index;

	int x = G[now].first, y = G[now].second;

	int z = 0;
	
	FOR(i, 0, 3) {
		int nxt = id2(x + dx[i], y + dy[i], 0);

		if (nxt == -1) continue;
		if (nxt == pa) continue;
		
		if (!dfn[nxt]) {
			tarjan(nxt, now); z++;
			if (low[nxt] >= dfn[now]) ge[now] = true;
			chkmin(low[now], low[nxt]);
		}
		else chkmin(low[now], dfn[nxt]);
	}

	if (!pa) ge[now] = (z >= 2);
}

char check3()
{
	if (n == 1 || m == 1) return true;
	
	int num = 0;
	
	FOR(i, 1, c) FOR(j, 0, 23) {
		int x = fx[i] + dx[j], y = fy[i] + dy[j];
		if (id(x, y) != -1) continue;
		if (id2(x, y, 0) != -1) continue;
		if (x >= 1 && x <= n && y >= 1 && y <= m) {
			int pos = ((x - 1) * 1ll * m + y) % MOD;
			if (fir2[pos] != T || fir3[pos] != 0) {fir2[pos] = T; fir3[pos] = 0; V2[pos].clear();}
			V2[pos].push_back(make_pair(make_pair(x, y), ++num));
			G[num] = make_pair(x, y);
		}
	}

	FOR(i, 1, num) dfn[i] = low[i] = ge[i] = 0; Index = 0;
	FOR(i, 1, num) if (!dfn[i]) tarjan(i, 0);

	FOR(i, 1, num) if (ge[i])
		FOR(j, 0, 7) if (id(G[i].first + dx[j], G[i].second + dy[j]) != -1) return true;
	return false;
}

void solve()
{
	in(n); in(m); in(c);

	FOR(i, 1, c) {
		int x, y; in(x); in(y);
		fx[i] = x; fy[i] = y;
		int pos = ((x - 1) * 1ll * m + y) % MOD;
		if (fir[pos] != T) {fir[pos] = T; V[pos].clear();}
		V[pos].push_back(make_pair(make_pair(x, y), i));
	}

	if (n * 1ll * m - c <= 1 || n * 1ll * m - c == 2 && check()) {puts("-1"); return;}
	if (!check2()) {puts("0"); return;}
	if (check3()) {puts("1"); return;}
	puts("2");
}

int main()
{
	in(T);
	memset(fir, 0x3f, sizeof fir);
	memset(fir2, 0x3f, sizeof fir2);
	memset(fir3, 0x3f, sizeof fir3);
	
	while (T--) solve();
	
	return 0;
}
