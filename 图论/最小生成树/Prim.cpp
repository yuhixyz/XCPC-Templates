int n, m;
int g[N][N];
int dist[N]; // dist[i]：i到集合的距离
bool st[N];

int prim() {
    memset(dist, 0x3f, sizeof dist);
    int res = 0; // 最小生成树的边权之和
    for (int i = 0; i < n; i++) {
        int t = -1; // 找到集合外距离集合最近的点
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }
        if (i && dist[t] == INF) return INF;  // 如果不是第一个点，并且这个点到集合已经不连通了，就返回
        if (i) res += dist[t]; // 不是第一个数, 把t加到最小生成树
        st[t] = true; // 把t加入集合
        // 用t->j的距离，更新集合外的j到集合的距离
        for (int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], g[t][j]);
        }
    }
    return res;
}