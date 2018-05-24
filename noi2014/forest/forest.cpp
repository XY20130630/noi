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

struct Edge {
	int x, y, a, b;
} edge[MAXN];

struct Node {
	char rev;
	int mx, data, id; Node *fa, *ch[2];
	Node() {mx = data = -1; rev = false; id = 0; fa = ch[0] = ch[1] = NULL;}

	void push();
	void splay();
	void access();
	void rotate();
	void update();
	void makerot();
	void pushdown();
	char is_top() {return !fa || fa -> ch[0] != this && fa -> ch[1] != this;}
} *to[MAXN << 1];

int n, m, tot;

char cmp(const Edge &x, const Edge &y) {return x.b < y.b;}

void Node::pushdown()
{
	if (rev) {
		if (ch[0]) std::swap(ch[0] -> ch[0], ch[0] -> ch[1]), ch[0] -> rev ^= 1;
		if (ch[1]) std::swap(ch[1] -> ch[0], ch[1] -> ch[1]), ch[1] -> rev ^= 1;
		rev = false;
	}
}

void Node::update()
{
	mx = data;
	if (ch[0]) chkmax(mx, ch[0] -> mx);
	if (ch[1]) chkmax(mx, ch[1] -> mx);
}

void Node::rotate()
{
	Node *pa = fa; fa = pa -> fa;
	if (!pa -> is_top()) {
		fa -> ch[fa -> ch[0] == pa ? 0 : 1] = this;
	}
	char dir = (pa -> ch[0] == this ? 0 : 1);
	pa -> ch[dir] = ch[dir ^ 1];
	if (ch[dir ^ 1]) ch[dir ^ 1] -> fa = pa; ch[dir ^ 1] = pa;
	pa -> fa = this; pa -> update(); update();
}

void Node::push() {if (!is_top()) fa -> push(); pushdown();}

void Node::splay()
{
	push();
	while (!is_top()) {
		if (fa -> is_top()) rotate();
		else {
			char dir = (fa -> ch[0] == this ? 0 : 1);
			if (fa -> fa -> ch[dir] == fa) fa -> rotate(), rotate();
			else rotate(), rotate();
		}
	}
}

void Node::access()
{
	Node *x = this;
	x -> splay(); x -> ch[1] = NULL;
	while (x -> fa != NULL) {
		x -> fa -> splay();	x -> fa -> ch[1] = x; x -> fa -> update(); x = x -> fa;
	}
}

void Node::makerot()
{
	access(); splay();
	rev ^= 1; std::swap(ch[0], ch[1]);
}

char is_connect(int x, int y)
{
	to[x] -> makerot();
	to[y] -> access(); to[y] -> splay();
	Node *t = to[x];
	while (t -> fa != NULL) t = t -> fa;
	return t == to[y];
}

void link(int x, int y)
{
	to[x] -> makerot(); to[x] -> fa = to[y];
}

void add(int x)
{
	Node *&now = to[++tot];
	now = new Node; now -> id = x;
	now -> mx = now -> data = edge[x].a;
	link(tot, edge[x].x); link(tot, edge[x].y);
}

void del(int x)
{
	to[edge[x].x] -> makerot();
	to[edge[x].y] -> access(); to[edge[x].y] -> splay();

	to[edge[x].y] -> pushdown();
	to[edge[x].y] -> ch[0] -> pushdown();

	if (!to[edge[x].y] -> ch[0] -> id) {
		delete to[edge[x].x] -> ch[1];

		to[edge[x].x] -> fa = NULL;
		to[edge[x].x] -> ch[1] = NULL;
		to[edge[x].y] -> ch[0] = NULL;
	}
	else {
		delete to[edge[x].y] -> ch[0];

		to[edge[x].x] -> fa = NULL;
		to[edge[x].y] -> ch[0] = NULL;
	}

	to[edge[x].x] -> update();
	to[edge[x].y] -> update();
}

int qmin(int x, int y)
{
	to[x] -> makerot();
	to[y] -> access(); to[y] -> splay();

	int get = to[y] -> mx;
	
	Node *t = to[y];

	while (t -> data != get) {
		t -> pushdown();
		if (t -> ch[0] && t -> ch[0] -> mx == get) t = t -> ch[0];
		else t = t -> ch[1];
	}

	return t -> id;
}

void addedge(int id)
{
	if (!is_connect(edge[id].x, edge[id].y)) add(id);
	else {
		int pre = qmin(edge[id].x, edge[id].y);
		if (edge[pre].a > edge[id].a) del(pre), add(id);
	}
}

int main()
{
	in(n); in(m);

	FOR(i, 1, n) to[i] = new Node; tot = n;
	FOR(i, 1, m) in(edge[i].x), in(edge[i].y), in(edge[i].a), in(edge[i].b);

	std::sort(edge + 1, edge + m + 1, cmp);

	int ans = 0x3f3f3f3f;
	
	FOR(i, 1, m) {
		if (edge[i].x == edge[i].y) continue;
		addedge(i);
		if (is_connect(1, n)) chkmin(ans, edge[i].b + edge[qmin(1, n)].a);
	}

	printf("%d\n", ans == 0x3f3f3f3f ? -1 : ans);
	
	return 0;
}
