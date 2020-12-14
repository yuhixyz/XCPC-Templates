int n, m;
int p[N];	// 并查集的父节点数组

struct Edge {
    int a, b, w;
    bool operator< (const Edge &W) const {
        return w < W.w;
    }
} edges[M];

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int kruskal() {
    sort(edges, edges + m);
    for (int i = 1; i <= n; i++ ) p[i] = i; // 初始化并查集
    int res = 0, cnt = 0; // res:最小生成树边权之和，cnt:当前加入的边数
    for (int i = 0; i < m; i++ ) {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;
        a = find(a), b = find(b);
        if (a != b) { // 不连通，就把这条边加到生成树里
            p[a] = b;
            res += w;
            cnt ++ ;
        }
    }
    if (cnt < n - 1) return INF;
    return res;
}