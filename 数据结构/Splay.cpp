#include <bits/stdc++.h>

using namespace std;

const int N = 100010, INF = 1e9;

int n, m;
int w[N];
struct Splay {
    int ch[2], fa, sz, val, flag; // flag=1为逆序标记
    void init(int _val, int _fa) {
        val = _val, fa = _fa;
        sz = 1, flag = 0;
        // ch[0] = ch[1] = 0; // 多测
    }
} tr[N];
int root;
int stk[N], top;

int get(int u) {
    return tr[tr[u].fa].ch[1] == u;
}

void pushup(int u) {
    tr[u].sz = tr[tr[u].ch[0]].sz + tr[tr[u].ch[1]].sz + 1;
}

void pushdown(int u) {
    if (tr[u].flag) {
        swap(tr[u].ch[0], tr[u].ch[1]);
        tr[tr[u].ch[0]].flag ^= 1;
        tr[tr[u].ch[1]].flag ^= 1;
        tr[u].flag = 0;
    }
}

void rotate(int u) {
    int fa = tr[u].fa, gfa = tr[fa].fa;
    int k = get(u);
    tr[gfa].ch[get(fa)] = u, tr[u].fa = gfa;
    tr[fa].ch[k] = tr[u].ch[k ^ 1], tr[tr[u].ch[k ^ 1]].fa = fa;
    tr[u].ch[k ^ 1] = fa, tr[fa].fa = u;
    pushup(fa), pushup(u);
}

// 把u转到v的下面
void splay(int u, int v) {
    while (tr[u].fa != v) {
        int fa = tr[u].fa, gfa = tr[fa].fa;
        if (gfa != v) {
            if (get(u) ^ get(fa)) rotate(u);
            else rotate(fa);
        }
        rotate(u);
    }
    if (!v) root = u; // v=0，说明u被转到根位置
}

// 将w[l~r]建成一棵splay，其根节点的父节点为fa
int build(int l, int r, int fa) {
    int u = stk[top--];
    int mid = l + r >> 1;
    tr[u].init(w[mid], fa);
    if (l < mid) tr[u].ch[0] = build(l, mid - 1, u);
    if (r > mid) tr[u].ch[1] = build(mid + 1, r, u);
    pushup(u);
    return u;
}

int kth(int k) {
    int u = root;
    while (u) {
        pushdown(u);
        if (tr[tr[u].ch[0]].sz >= k) u = tr[u].ch[0];
        else if (tr[tr[u].ch[0]].sz + 1 == k) return u;
        else k -= tr[tr[u].ch[0]].sz + 1, u = tr[u].ch[1];
    }
    return -1;
}

// // 结点u内存回收
// void dfs(int u) {
//     stk[++top] = u;
//     if (tr[u].ch[0]) dfs(tr[u].ch[0]);
//     if (tr[u].ch[1]) dfs(tr[u].ch[1]);
// }

void print(int u) { // 中序遍历输出序列
    pushdown(u);
    if (tr[u].ch[0]) print(tr[u].ch[0]);
    if (tr[u].val != INF && tr[u].val != -INF) printf("%d ", tr[u].val);
    if (tr[u].ch[1]) print(tr[u].ch[1]);
}

int main() {
    for (int i = 1; i < N; i++) stk[++top] = i; // 内存复用
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) w[i] = i; // w[1~n]为需要维护的序列，一般为题目输入
    w[0] = -INF, w[n + 1] = INF; // 哨兵
    root = build(0, n + 1, 0);
    while (m--) {
        int l, r; scanf("%d%d", &l, &r);
        // 找到[l+1,r+1]的前后
        l = kth(l), r = kth(r + 2);
        splay(l, 0), splay(r, l); // 将l转到根，r转到l下面，此时r的左孩子就表示需要维护的区间
        tr[tr[r].ch[0]].flag ^= 1;
    }
    print(root);
    return 0;
}