#include <iostream>

using namespace std;

const int N = 50010;

int n, m;
struct Tree {
	int l, r;
	int lmax, rmax;
} tr[N << 2];
int stk[N], top;

void pushup(Tree &root, Tree &left, Tree &right) {
	root.lmax = left.lmax, root.rmax = right.rmax;
	if (left.r - left.l + 1 == left.lmax) root.lmax += right.lmax;
	if (right.r - right.l + 1 == right.rmax) root.rmax += left.rmax;
}

void pushup(int u) {
	pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
	if (l == r) {
		tr[u] = {l, r, 1, 1};
	} else {
		tr[u] = {l, r};
		int mid = l + r >> 1;
		build(u << 1, l, mid); build(u << 1 | 1, mid + 1, r);
		pushup(u);
	} 
}

void modify(int u, int x, int y) {
	if (tr[u].l == x && tr[u].r == x) {
		tr[u].lmax = tr[u].rmax = y;
	} else {
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) modify(u << 1, x, y);
		else modify(u << 1 | 1, x, y);
		pushup(u);
	}
}

int query(int u, int x) {
	if (tr[u].l == x && tr[u].r == x) {
		return tr[u].lmax;
	} else {
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) {
			if (tr[u << 1].r - tr[u << 1].rmax + 1 <= x) {
				return tr[u << 1].rmax + tr[u << 1 | 1].lmax;				
			} else {
				return query(u << 1, x);
			}
		} else {
			if (tr[u << 1 | 1].l + tr[u << 1 | 1].lmax - 1 >= x) {
				return tr[u << 1 | 1].lmax + tr[u << 1].rmax;
			} else {
				return query(u << 1 | 1, x);
			}
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &m) != EOF) {
		build(1, 1, n);
		while (m--) {
			char op[2]; int x;
			scanf("%s", op);
			if (*op == 'D') {
				scanf("%d", &x);
				modify(1, x, 0);
				stk[++top] = x;
			} else if (*op == 'R') {
				int x = stk[top--];
				modify(1, x, 1);
			} else {
				scanf("%d", &x);
				printf("%d\n", query(1, x));		
			}
		}
	}
	return 0;
}
