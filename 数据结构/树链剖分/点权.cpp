#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100010, M = N << 1;

int n, m;
int a[N], na[N]; // na表示新编号
int h[N], e[M], ne[M], idx;
struct Tree {
    int l, r;
    LL sum, add;
} tr[N << 2];
int dfn[N], ts; // dfn表示dfs序（优先遍历重儿子）
int dep[N], sz[N], top[N], fa[N], son[N];
// dep[i]表示i的深度（根节点的深度为1）,sz[i]表示以i为根的子树的大小
// top[i]表示i所在重链的顶点，fa[i]表示i的父结点，son[i]表示子树i的重儿子

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs1(int u, int father, int depth) {
    dep[u] = depth, fa[u] = father, sz[u] = 1;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == father) continue;
        dfs1(j, u, depth + 1);
        sz[u] += sz[j];
        if (sz[son[u]] < sz[j]) son[u] = j;
    }
}

// 点u所属的重链的顶点为t
void dfs2(int u, int t) {
    dfn[u] = ++ts, na[ts] = a[u], top[u] = t;
    if (!son[u]) return; // u为叶结点
    dfs2(son[u], t); // 重儿子
    // 处理轻儿子
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa[u] || j == son[u]) continue;
        dfs2(j, j); // 轻儿子所处重链的顶点就是自己 
    }
}

void pushup(int u) {
    tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, na[r], 0};
    } else {
        tr[u] = {l, r};
        int mid = l + r >> 1;
        build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }
}

void pushdown(int u) {
    auto &root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.sum += root.add * (left.r - left.l + 1);
        right.add += root.add, right.sum += root.add * (right.r - right.l + 1);
        root.add = 0;
    }
}

// 将[l,r]区间加上k
void update(int u, int l, int r, int k) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].add += k;
        tr[u].sum += k * (tr[u].r - tr[u].l + 1);
        return;
    }
    pushdown(u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) update(u << 1, l, r, k);
    if (r > mid) update(u << 1 | 1, l, r, k);
    pushup(u);
}

// 求[l,r]区间和
LL query(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }
    pushdown(u); // 下传add标记
    LL res = 0;
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) res += query(u << 1, l, r);
    if (r > mid) res += query(u << 1 | 1, l, r);
    return res;
}

// 将树上u->v的路径全部加上k
void update_path(int u, int v, int k) {
    while (top[u] != top[v]) { // u,v不在同一个重链上
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        // 加上u所在的重链和和
        // 其区间为[dfn[top[u]], dfn[u]]
        update(1, dfn[top[u]], dfn[u], k);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    // 加上u-v之间路径的和
    update(1, dfn[v], dfn[u], k);
}

// 求树上u-v之间的路径和
LL query_path(int u, int v) {
    LL res = 0;
    while (top[u] != top[v]) { // u,v不在同一个重链上
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        // 加上u所在的重链和和
        // 其区间为[dfn[top[u]], dfn[u]]
        res += query(1, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] < dep[v]) swap(u, v);
    // 加上u-v之间路径的和
    res += query(1, dfn[v], dfn[u]);
    return res;
}

// 将树上以u为根的子树全部加上k
void update_tree(int u, int k) {
    // 对应区间 [dfn[u], dfn[u]+sz[u]-1]
    update(1, dfn[u], dfn[u] + sz[u] - 1, k);
}

// 求树上以u为根的子树的和
LL query_tree(int u) {
    // 对应区间 [dfn[u], dfn[u]+sz[u]-1]
    return query(1, dfn[u], dfn[u] + sz[u] - 1);
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    dfs1(1, -1, 1); // 预处理dep,fa,sz
    dfs2(1, 1); // 求dfs序dfn,top
    build(1, 1, n); // 建立线段树
    for (scanf("%d", &m); m--; ) {
        int type, u, v, k;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d%d", &u, &v, &k);
            update_path(u, v, k);
        } else if (type == 2) {
            scanf("%d%d", &u, &k);
            update_tree(u, k);
        } else if (type == 3) {
            scanf("%d%d", &u, &v);
            printf("%lld\n", query_path(u, v));
        } else {
            scanf("%d", &u);
            printf("%lld\n", query_tree(u));
        }
    }
    return 0;
}