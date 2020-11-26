// 例子：维护区间加法区间求和
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m;
LL a[N];
struct Tree {
    int l, r;
    LL sum, add;
} tr[N << 2];

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, a[r], 0};
    } else {
        tr[u] = {l, r};
        int mid = tr[u].l + tr[u].r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void pushdown(int u) { // 先下方标记，再清空标记
    Tree &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    left.add += root.add, left.sum += (LL)(left.r - left.l + 1) * root.add;
    right.add += root.add, right.sum += (LL)(right.r - right.l + 1) * root.add;
    root.add = 0;
}

void modify(int u, int l, int r, LL y) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].sum += (tr[u].r - tr[u].l + 1) * y;
        tr[u].add += y;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, y);
        if (r > mid) modify(u << 1 | 1, l, r, y);
        pushup(u);
    }
}

LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    } else {
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        LL res = 0;
        if (l <= mid) res += query(u << 1, l, r);
        if (r > mid) res += query(u << 1 | 1, l, r);
        return res;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    build(1, 1, n);
    char op[2];
    int l, r;
    while (m--) {
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'C') {
            LL d;
            scanf("%lld", &d);
            modify(1, l, r, d);
        } else {
            printf("%lld\n", query(1, l, r));
        }
    }
    return 0;
}