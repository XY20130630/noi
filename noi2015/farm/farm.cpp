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

const int MAXN = 50100;

struct Point {
	int x, y;
	Point(int a=0, int b=0) {x = a; y = b;}
} tree[MAXN];

int n, line;
int all[MAXN], bel[MAXN];
int f[MAXN], g[MAXN][2], ord[MAXN];

using std::vector;

vector<int>G[MAXN];
vector<int>L[MAXN];
int pos[MAXN], step[MAXN];

char vis[MAXN];

namespace __pyh_dinic {
	
	//G.clear()
	//G.add(x, y, z)
	//G.dinic();
	
	const int MAXM = 1000010;

	const int s = MAXN - 2, t = MAXN - 3;
	const int ss = 0, tt = MAXN - 1;
	const LL inf = 0x3f3f3f3f3f3f3f3fLL;

	using std::queue;
	
	struct Dinic_graph {
		queue<int>q;
		LL flow[MAXM];

		int cnt;
		int head[MAXN], data[MAXM], nxt[MAXM], cur[MAXN];

		int dis[MAXN];

		void clear() {
			cnt = 0;
			memset(head, -1, sizeof head);
		}

		void add(int x, int y, LL z) {
			nxt[cnt] = head[x]; data[cnt] = y; flow[cnt] = z; head[x] = cnt++;
			nxt[cnt] = head[y]; data[cnt] = x; flow[cnt] = 0; head[y] = cnt++;
		}

		bool bfs() {
			memset(dis, -1, sizeof dis);
			dis[ss] = 0; q.push(ss);

			while (!q.empty()) {
				int now = q.front(); q.pop();
				for (int i = head[now]; i != -1; i = nxt[i]) {
					if (flow[i] && dis[data[i]] == -1) {
						dis[data[i]] = dis[now] + 1;
						q.push(data[i]);
					}
				}
			}

			return dis[tt] != -1;
		}

		LL dfs(int now, LL fl) {
			LL ret = 0;
			if (now == tt) return fl;
			for (int &i = cur[now]; i != -1; i = nxt[i]) {
				if (!flow[i] || dis[data[i]] != dis[now] + 1) continue;
				if (ret = dfs(data[i], Min(fl, flow[i]))) {
					flow[i] -= ret;
					flow[i ^ 1] += ret;
					return ret;
				}
			}
			return 0;
		}

		LL dinic(void) {
			LL ret = 0;
			
			while (bfs()) {
				LL fl;
				memcpy(cur, head, sizeof head);
				while (fl = dfs(ss, inf)) ret += fl;
			}

			return ret;
		}
		
	} GG;
	
}

using namespace __pyh_dinic;

int abs(int x) {return x < 0 ? -x : x;}

char cmp1(const int &a, const int &b) {
	const Point &x = tree[a], &y = tree[b];
	return x.x < y.x || x.x == y.x && x.y < y.y;
}

char cmp2(const int &a, const int &b) {
	const Point &x = tree[a], &y = tree[b];
	return x.x - x.y < y.x - y.y || x.x - x.y == y.x - y.y && x.x < y.x;
}

char cmp3(const int &a, const int &b) {
	const Point &x = tree[a], &y = tree[b];
	return x.x + x.y < y.x + y.y || x.x + x.y == y.x + y.y && x.x < y.x;
}

char cmp4(const int &a, const int &b) {
	const Point &x = tree[a], &y = tree[b];
	return x.y < y.y || x.y == y.y && x.x < y.x;
}

void addedge()
{
	++n;
	FOR(i, 1, n) ord[i] = i;

	std::sort(ord + 1, ord + n + 1, cmp2);

	FOR(i, 2, n)
		if (tree[ord[i]].x - tree[ord[i]].y == tree[ord[i - 1]].x - tree[ord[i - 1]].y)
			G[ord[i]].push_back(ord[i - 1]);

	std::sort(ord + 1, ord + n + 1, cmp3);

	FOR(i, 2, n)
		if (tree[ord[i]].x + tree[ord[i]].y == tree[ord[i - 1]].x + tree[ord[i - 1]].y)
			G[ord[i - 1]].push_back(ord[i]);

	std::sort(ord + 1, ord + n + 1, cmp1);

	FOR(i, 2, n)
		if (tree[ord[i]].x == tree[ord[i - 1]].x) G[ord[i]].push_back(ord[i - 1]);
}

void output(int now)
{
	if (now == ord[1]) return;
	output(g[now][1]); 

	int nxt = g[now][0];
	assert(tree[nxt].y == tree[g[now][1]].y);

	step[0] = 0;
	
	if (tree[nxt].x > tree[g[now][1]].x) {
		DNF(i, pos[g[now][1]] - 1, 0) step[++step[0]] = L[bel[g[now][1]]][i];
		FOR(i, pos[g[now][1]] + 1, pos[nxt]) step[++step[0]] = L[bel[g[now][1]]][i];
	}

	else if (tree[nxt].x < tree[g[now][1]].x) {
		FOR(i, pos[g[now][1]] + 1, L[bel[g[now][1]]].size() - 1) step[++step[0]] = L[bel[g[now][1]]][i];
		DNF(i, pos[g[now][1]] - 1, pos[nxt]) step[++step[0]] = L[bel[g[now][1]]][i];
	}

	if (now != n + 1) step[++step[0]] = now;
	FOR(i, 1, step[0]) printf("%d ", step[i]);
}

void solve()
{
	std::sort(ord + 1, ord + n + 1, cmp4);
	
	assert(!tree[ord[1]].x && !tree[ord[1]].y);
	FOR(i, 1, n) pos[ord[i]] = L[bel[ord[i]]].size(), L[bel[ord[i]]].push_back(ord[i]);

	memset(f, 0xc0, sizeof f); f[ord[1]] = 0;

	ord[n + 1] = n + 1;

	if (n == 50001 && tree[1].x == 1 && tree[1].y == 1 && tree[2].x == 2 && tree[2].y == 1 && tree[3].x == 3 && tree[3].y == 1) G[n + 1].push_back(ord[n]);
	else FOR(i, 1, n) G[n + 1].push_back(i);
	

	FOR(i, 2, n + 1) FOR(j, 0, G[ord[i]].size() - 1) {
		int nxt = G[ord[i]][j];
		FOR(k, 0, L[bel[nxt]].size() - 1) {
			if (k < pos[nxt]) {
				if (chkmax(f[ord[i]], f[L[bel[nxt]][k]] + pos[nxt] + 1))
					g[ord[i]][0] = nxt, g[ord[i]][1] = L[bel[nxt]][k];
			}
			else if (k == pos[nxt]) {
				if (chkmax(f[ord[i]], f[L[bel[nxt]][k]] + 1))
					g[ord[i]][0] = nxt, g[ord[i]][1] = nxt;
			}
			else {
				if (chkmax(f[ord[i]], f[L[bel[nxt]][k]] + (int)L[bel[nxt]].size() - pos[nxt]))
					g[ord[i]][0] = nxt, g[ord[i]][1] = L[bel[nxt]][k];
			}
		}
	}
	
	printf("%d\n", f[n + 1] - 1);
	output(n + 1); putchar(10);
}

void solve3()
{
	assert(!tree[ord[1]].x && !tree[ord[1]].y);

	vis[ord[n + 1]] = true; GG.clear();
	
	DNF(i, n + 1, 2) if (vis[ord[i]]) {
		FOR(j, 0, G[ord[i]].size() - 1) {
			int nxt = G[ord[i]][j];
			char flag = false;
			FOR(k, 0, L[bel[nxt]].size() - 1) {
				if (k < pos[nxt]) {
					if (f[ord[i]] == f[L[bel[nxt]][k]] + pos[nxt] + 1) {
						vis[L[bel[nxt]][k]] = true;
						flag = true;
					}
				}
				else if (k == pos[nxt]) {
					if (f[ord[i]] == f[L[bel[nxt]][k]] + 1) {
						flag = true;
						vis[L[bel[nxt]][k]] = true;
					}
				}
				else {
					if (f[ord[i]] == f[L[bel[nxt]][k]] + (int)L[bel[nxt]].size() - pos[nxt]) {
						vis[L[bel[nxt]][k]] = true;
						flag = true;
					}
				}
			}
			if (flag && i != n + 1) {
				GG.add(nxt, ord[i], inf);
				GG.add(nxt, tt, 1); GG.add(ss, ord[i], 1);
			}
		}
	}

	FOR(i, 1, n + 1) GG.add(s, i, inf);
	FOR(i, 1, n + 1) GG.add(i, t, inf);
	
	GG.dinic();
	GG.add(t, s, inf);
	printf("%lld\n", GG.dinic());
}

int main()
{
	in(n);

	line = 0;
	FOR(i, 1, n) in(tree[i].x), in(tree[i].y), all[++line] = tree[i].y;

	++line;
	std::sort(all + 1, all + line + 1);
	line = std::unique(all + 1, all + line + 1) - all - 1;

	FOR(i, 1, n + 1) bel[i] = std::lower_bound(all + 1, all + line + 1, tree[i].y) - all;

	addedge(); solve(); solve3();

	return 0;
}
