#include <bits/stdc++.h>

using namespace std;

const int N = 20010, M = N * 2;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
int fa[N][16], depth[N];
int dist[N], q[N]; // dist[]维护到根距离

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void bfs(int root) {
    int hh = 0, tt = 0;
    memset(depth, -1, sizeof depth);
    memset(dist, 0x3f, sizeof dist);
    q[0] = root, dist[root] = 0;
    depth[0] = 0, depth[root] = 1;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (depth[j] == -1) {
                depth[j] = depth[t] + 1;
                dist[j] = dist[t] + w[i];
                q[++tt] = j;
                fa[j][0] = t;
                for (int k = 1; k <= 15; k++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    for (int k = 15; k >= 0; k--) {
        if (depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    }
    if (a == b) return a;
    for (int k = 15; k >= 0; k--) {
        if (fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    }
    return fa[a][0];
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    bfs(1);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        int p = lca(x, y);
        printf("%d\n", dist[x] + dist[y] - 2 * dist[p]);
    }
    return 0;
}