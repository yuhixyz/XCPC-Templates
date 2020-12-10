// 1表示空闲
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int N = 100010;

int T, Case, n, m;
struct Tree {
    int l, r;
    int same[2], lmax[2], rmax[2], tmax[2]; // 下标0维护分配给屌丝的时间，下标1维护分配给女神的时间
} tr[N << 2];

void pushup(int u, int type) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    root.lmax[type] = left.lmax[type];
    if (left.lmax[type] == left.r - left.l + 1) root.lmax[type] += right.lmax[type];
    root.rmax[type] = right.rmax[type];
    if (right.rmax[type] == right.r - right.l + 1) root.rmax[type] += left.rmax[type];
    root.tmax[type] = max(max(left.tmax[type], right.tmax[type]), left.rmax[type] + right.lmax[type]);
}

void build(int u, int l, int r) {
    tr[u] = {l, r, -1, -1, 1, 1, 1, 1, 1, 1};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u, 0), pushup(u, 1);
}

void pushdown(int u, int type) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.same[type] != -1) {
        left.same[type] = right.same[type] = root.same[type];
        left.lmax[type] = left.rmax[type] = left.tmax[type] = root.same[type] * (left.r - left.l + 1);
        right.lmax[type] = right.rmax[type] = right.tmax[type] = root.same[type] * (right.r - right.l + 1);
        root.same[type] = -1;
    }
}

void modify(int u, int l, int r, int x, int type) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].same[type] = x;
        tr[u].lmax[type] = tr[u].rmax[type] = tr[u].tmax[type] = x * (tr[u].r - tr[u].l + 1);
    } else {
        pushdown(u, type);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, x, type);
        if (r > mid) modify(u << 1 | 1, l, r, x, type);
        pushup(u, type);
    }
}

// 找到第一段长度为x的连续空闲区间的左端点
int query(int u, int x, int type) {
    if (tr[u].tmax[type] < x) return -1; // 不存在
    pushdown(u, type);
    if (tr[u << 1].tmax[type] >= x) return query(u << 1, x, type);
    if (tr[u << 1].rmax[type] + tr[u << 1 | 1].lmax[type] >= x) return tr[u << 1].r - tr[u << 1].rmax[type] + 1;
    return query(u << 1 | 1, x, type);
}

int main() {
    for (cin >> T; T--; ) {
        printf("Case %d:\n", ++Case);
        scanf("%d%d", &n, &m);
        build(1, 1, n);
        while (m--) {
            char op[10];
            int x, y;
            scanf("%s", op);
            if (*op == 'N') {
                scanf("%d", &x);
                int st = query(1, x, 0); // 先在屌丝时间轴查询是否存在长度为x的连续空闲(1)区间
                if (st != -1) { // 在屌丝时间轴查到了,同时修改两个时间轴的区间[st,st+x-1]置为忙碌状态
                    modify(1, st, st + x - 1, 0, 0);
                    modify(1, st, st + x - 1, 0, 1);
                    printf("%d,don't put my gezi\n", st);
                } else { // 屌丝时间轴中没有这样的区间
                    st = query(1, x, 1); // 在女神时间轴中查
                    if (st != -1) { // 在女神时间轴查到,就同时修改两个时间轴的区间[st,st+x-1]置为忙碌状态
                        modify(1, st, st + x - 1, 0, 0);
                        modify(1, st, st + x - 1, 0, 1);
                        printf("%d,don't put my gezi\n", st);
                    } else { // 没有空闲时间
                        puts("wait for me");
                    }
                }
            } else if (*op == 'D') {
                scanf("%d", &x);
                int st = query(1, x, 0);
                if (st != -1) { // 在屌丝时间轴查到了，区间修改为忙碌状态
                    modify(1, st, st + x - 1, 0, 0);
                    printf("%d,let's fly\n", st);
                } else { // 没有空闲时间
                    puts("fly with yourself");
                }
            } else { // 由于是三分钟热度，应该是将区间置为空闲状态
                scanf("%d%d", &x, &y);
                modify(1, x, y, 1, 0);
                modify(1, x, y, 1, 1);
                puts("I am the hope of chinese chengxuyuan!!");
            }
        }
    }
    return 0;
}
