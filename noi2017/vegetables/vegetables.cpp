#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> bool chkmax(Tp &x, Tp y) {return x > y ? 0 : (x=y,1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x < y ? 0 : (x=y,1);}
template <typename Tp> Tp Max(Tp x, Tp y) {return x > y ? x : y;}
template <typename Tp> Tp Min(Tp x, Tp y) {return x < y ? x : y;}

class fast_input {
private:
	static const int SIZE = 1 << 15 | 1;
	char buf[SIZE], *front, *back;

	void Next(char &c) {
	    if(front == back) back = (front = buf) + fread(buf, 1, SIZE, stdin);
		c = front == back ? (char)EOF : *front++;
	}

public :
	template<class T>void operator () (T &x) {
		char c, f = 1;
		for(Next(c); !isdigit(c); Next(c)) if(c == '-') f = -1;
		for(x = 0; isdigit(c); Next(c)) x = x * 10 + c - '0';
		x *= f;
	}
	void operator () (char &c, char l = 'a', char r = 'z') {
		for(Next(c); c > r || c < l; Next(c)) ;
	}
}in;

const int MAXN = 1000010;

int n, m, k;
LL ans[MAXN];

struct Obj {
	int a, x, c;
} obj[MAXN];

int num, g[MAXN], sum[MAXN], fa[MAXN];

bool cmp(const Obj &x, const Obj &y)
{
	return x.a > y.a;
}

inline int find(int x)
{
	while (x != fa[x]) x = fa[x] = fa[fa[x]]; return x;
}

int main()
{
	in(n); in(m); in(k);

	FOR(i, 1, n) {
		int a, s, c, x;
		in(a); in(s); in(c); in(x);

		++num;
		obj[num].a = a;
		obj[num].x = x;
		obj[num].c = c - 1;

		++num;
		obj[num].a = a + s;
		obj[num].x = -1;
		if (!x) obj[num].c = 100000;
		else obj[num].c = (c - 1) / x + 1;
	}

	std::sort(obj + 1, obj + num + 1, cmp);

	FOR(i, 0, 100000) fa[i] = i;

	int tot = 0; LL ret = 0;
	
	FOR(i, 1, num) {
		if (obj[i].x == -1) {
			int fx = find(Min(obj[i].c, 100000));

			if (!fx) continue;
			
			g[++tot] = obj[i].a;
			ret += obj[i].a;
			if ((++sum[fx]) == m) fa[fx] = fx - 1;
		}
		else {
			int end;
			if (!obj[i].x) end = 100000;
			else end = Min(100000, (obj[i].c - 1) / obj[i].x + 1);
			
			int fx = find(end);
			int lef = obj[i].c - obj[i].x * (fx - 1);
			
			while (fx > 0) {
				while (lef > 0 && sum[fx] != m) {
					lef--; sum[fx]++; g[++tot] = obj[i].a; ret += obj[i].a;
				}

				if (!lef && !obj[i].x) break;
				
				if (sum[fx] == m) fa[fx] = fx - 1;

				int tmp = find(fx - 1);
				lef += (fx - tmp) * obj[i].x;
				fx = tmp;
			}
		}
	}

	int all = tot;
	tot = 100000 * m;

	ans[100000] = ret;
	
	DNF(i, 99999, 1) {
		ans[i] = ans[i + 1];

		if (tot - m > all) {
			tot -= m;
			continue;
		}
		
		int tmp = m;
		while (tmp--) ans[i] -= g[tot--];
	}

	FOR(i, 1, k) {
		int x; in(x); printf("%lld\n", ans[x]);
	}
	
	return 0;
}
