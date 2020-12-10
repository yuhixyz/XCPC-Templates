#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int N = 100010, mod = 10007;

int n, m;
struct Tree {
	int l, r;
	LL same, mul, add, s[3];
 } tr[N << 2];

void build(int u, int l, int r) {
	tr[u] = {l, r, 0, 1, 0, 0, 0, 0};
	if (l == r) return;
	int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void pushup(int u) {
	for (int i = 0; i < 3; i++) {
		tr[u].s[i] = (tr[u << 1].s[i] + tr[u << 1 | 1].s[i]) % mod;
	}
}

void pushdown(int u) {
	auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
	if (root.same) {
		left.same = right.same = root.same;
		left.mul = right.mul = 1, left.add = right.add = 0;
		LL base = 1;
		for (int i = 0; i < 3; i++) {
			(base *= root.same) %= mod;
			left.s[i] = (left.r - left.l + 1) * base % mod;
			right.s[i] = (right.r - right.l + 1) * base % mod; 
		}
		root.same = 0;
	}
	if (root.mul != 1) {
		LL k = root.mul;
		(left.mul *= k) %= mod, (right.mul *= k) %= mod;
		(left.add *= k) %= mod, (right.add *= k) %= mod;
		LL base = 1;
		for (int i = 0; i < 3; i++) {
			(base *= k) %= mod;
			(left.s[i] *= base) %= mod, (right.s[i] *= base) %= mod;
		}
		root.mul = 1;
	}
	if (root.add) {
		LL a = root.add;
		(left.add += a) %= mod, (right.add += a) %= mod;
		(left.s[2] += 3 * a * left.s[1] + 3 * a * a * left.s[0] + (left.r - left.l + 1) * a * a * a) %= mod;
		(right.s[2] += 3 * a * right.s[1] + 3 * a * a * right.s[0] + (right.r - right.l + 1) * a * a * a) %= mod;
		(left.s[1] += 2 * a * left.s[0] + (left.r - left.l + 1) * a * a) %= mod;
		(right.s[1] += 2 * a * right.s[0] + (right.r - right.l + 1) * a * a) %= mod;
		(left.s[0] += (left.r - left.l + 1) * a) %= mod, (right.s[0] += (right.r - right.l + 1) * a) %= mod;
		root.add = 0;
	}
}

// [l,r]乘k再加a
void modify_mul_add(int u, int l, int r, LL k, LL a) {
	if (tr[u].l >= l && tr[u].r <= r) {
		if (k != 1) {
			(tr[u].mul *= k) %= mod;
			(tr[u].add *= k) %= mod;
			LL base = 1;
			for (int i = 0; i < 3; i++) {
				(base *= k) %= mod;
				(tr[u].s[i] *= base) %= mod;
			}
		}
		if (a) {
			(tr[u].add += a) %= mod;
			(tr[u].s[2] += 3 * a * tr[u].s[1] + 3 * a * a * tr[u].s[0] + (tr[u].r - tr[u].l + 1) * a * a * a) %= mod;
			(tr[u].s[1] += 2 * a * tr[u].s[0] + (tr[u].r - tr[u].l + 1) * a * a) %= mod;
			(tr[u].s[0] += (tr[u].r - tr[u].l + 1) * a) %= mod;
		}
	} else {
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify_mul_add(u << 1, l, r, k, a);
		if (r > mid) modify_mul_add(u << 1 | 1, l, r, k, a);
		pushup(u);
	}
} 

void modify_assign(int u, int l, int r, int c) {
	if (tr[u].l >= l && tr[u].r <= r) {
		tr[u].same = c, tr[u].mul = 1, tr[u].add = 0;
		LL base = 1;
		for (int i = 0; i < 3; i++) {
			(base *= tr[u].same) %= mod;
			tr[u].s[i] = (tr[u].r - tr[u].l + 1) * base % mod;
		}
	} else {
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify_assign(u << 1, l, r, c);
		if (r > mid) modify_assign(u << 1 | 1, l, r, c);
		pushup(u);
	}
}

LL query(int u, int l, int r, int type) {
	if (tr[u].l >= l && tr[u].r <= r) {
		return tr[u].s[type];
	} else {
		pushdown(u);
		LL res = 0;
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) (res += query(u << 1, l, r, type)) %= mod;
		if (r > mid) (res += query(u << 1 | 1, l, r, type)) %= mod;
		return res;
	}
}

int main() {
	 while (cin >> n >> m && n && m) {
		 build(1, 1, n);
		 while (m--) {
			 int type, x, y, c;
			 scanf("%d%d%d%d", &type, &x, &y, &c);
			 if (type == 1) {
				 modify_mul_add(1, x, y, 1ll, c);
			 } else if (type == 2) {
				modify_mul_add(1, x, y, c, 0ll);
			 } else if (type == 3) {
				modify_assign(1, x, y, c);
			 } else {
				printf("%lld\n", query(1, x, y, c - 1));
			 }
		 }
	 }
	 return 0;
 }
