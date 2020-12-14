#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100010, M = 300010;

int n, m;
int h[N], e[N * 2], w[N * 2], ne[N * 2], idx;
struct Edge {
    int a, b, w;
    bool f;
    bool operator < (const Edge &W) const {
        return w < W.w;
    }
} edge[M];
int p[N], q[N];
int d1[N][17], d2[N][17];
int fa[N][17], depth[N];
// fa[i][j]:从i开始向上跳2^j步所能到的点
// d1[i][j]:从i开始向上跳2^j步所经过路径上的最大边
// d2[i][j]:从i开始向上跳2^j步所经过路径上的次大边

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void update(int d1, int d2, int &v1, int &v2) {
    if (d1 > v1) v2 = max(v1, d2), v1 = d1;
    else if (d1 == v1) v2 = max(v2, d2);
    else v2 = max(v2, d1);
}

void bfs(int root) {
    memset(depth, -1, sizeof depth);
    depth[0] = 0, depth[root] = 1;
    int hh = 0, tt = 0;
    q[0] = root;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] == -1) {
                depth[j] = depth[t] + 1;
                q[++tt ] = j;
                fa[j][0] = t;
                d1[j][0] = w[i], d2[j][0] = INT_MIN;
                for (int k = 1; k <= 16; k++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                    int mid = fa[j][k - 1];
                    update(d1[j][k - 1], d2[j][k - 1], d1[j][k], d2[j][k]);
                    update(d1[mid][k - 1], d2[mid][k - 1], d1[j][k], d2[j][k]);
                }
            }
        }
    }
}

LL kruskal() {
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(edge, edge + m);
    LL res = 0;
    for (int i = 0; i < m; i++) {
        int a = edge[i].a, b = edge[i].b, w = edge[i].w;
        int pa = find(a), pb = find(b);
        if (pa != pb) {
            add(a, b, w), add(b, a, w);
            edge[i].f = true;
            p[pa] = pb;
            res += w;
        }
    }
    return res;
}

void lca(int a, int b, int &v1, int &v2) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 16; k >= 0; k--) {
        if (depth[fa[a][k]] >= depth[b]) {
            update(d1[a][k], d2[a][k], v1, v2);
            a = fa[a][k];
        }
    }
    if (a == b) return;
    for (int k = 16; k >= 0; k--) {
        if (fa[a][k] != fa[b][k]) {
            update(d1[a][k], d2[a][k], v1, v2);
            update(d1[b][k], d2[b][k], v1, v2);
            a = fa[a][k], b = fa[b][k];
        }
    }
    update(d1[a][0], d2[a][0], v1, v2);
    update(d1[b][0], d2[b][0], v1, v2);
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        edge[i] = {a, b, w};
    }
    LL mins = kruskal();
    bfs(1);
    LL res = 1e18;
    for (int i = 0; i < m; i++) {
        if (!edge[i].f) {
            int a = edge[i].a, b = edge[i].b, w = edge[i].w;
            int v1 = INT_MIN, v2 = INT_MIN;
            lca(a, b, v1, v2);
            if (v1 < w) res = min(res, mins + w - v1);
            else if (v2 < w) res = min(res, mins + w - v2);
        }
    }
    printf("%lld\n", res);
    return 0;
}