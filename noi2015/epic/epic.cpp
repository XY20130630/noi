#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void out(Tp x) {
	if (x > 9) out(x / 10);
	putchar(x % 10 + '0');
	return;
}

template <typename Tp> Tp Max(const Tp &x, const Tp &y) {return x > y ? x : y;}
template <typename Tp> Tp Min(const Tp &x, const Tp &y) {return x < y ? x : y;}
template <typename Tp> bool chkmax(Tp &x, Tp y) {return x >= y ? 0 : (x=y, 1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x <= y ? 0 : (x=y, 1);}

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


int n, k;

struct Pair {
	LL first; int second;
	Pair(LL x=0, int y=0) {first = x, second = y;}
	bool operator < (const Pair &another) const {return first > another.first || first == another.first && second > another.second;}
	bool operator > (const Pair &another) const {return first < another.first || first == another.first && second < another.second;}
};

//using std::pair;
//using std::make_pair;
//using std::priority_queue;

//priority_queue<pair<LL, int>, std::vector<pair<LL, int> >, std::greater<pair<LL, int> > >q;

const int MAXN = 200010;

Pair q[MAXN];

int main()
{
	in(n); in(k);
	int need = (k - 1 - (n - 1) % (k - 1)) % (k - 1);

	FOR(i, 1, need) q[i] = Pair(0, 0);
	FOR(i, 1, n) {LL w; in(w); q[i + need] = Pair(w, 0);}

	int num = n + need;
	std::make_heap(q + 1, q + num + 1);

	LL ans = 0;
	
	while (num != 1) {
		LL w = 0; int d = 0;
		FOR(i, 1, k) {
			ans += q[1].first, w += q[1].first, chkmax(d, q[1].second), std::pop_heap(q + 1, q + num + 1), num--;
		}
		q[++num] = Pair(w, d + 1); std::push_heap(q + 1, q + num + 1);
	}

	printf("%lld\n%d\n", ans, q[1].second);

	return 0;
}
