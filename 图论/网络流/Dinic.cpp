#include <bits/stdc++.h>

using namespace std;

const int N = 100010, M = 200010, INF = 1e9;

int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
int q[N];
int d[N], cur[N]; // d[i]表示点i的层次，cur[i]表示i的当前弧

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() { // 判断残留网络是否存在增广路（即从S到T存在边全大于0的路径）
    int hh = 0, tt = -1;
    memset(d, -1, sizeof d);
    q[++tt] = S, d[S] = 0, cur[S] = h[S];
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (d[j] == -1 && w[i]) {
                d[j] = d[t] + 1;
                cur[j] = h[j];
                q[++tt] = j;
                if (j == T) return true; // 找到了增广路，此时增广路的流量即f[T]
            }
        }
    }
    return false; // 残留网络不存在增广路，那么此时原图的可行流流量就是最大流
}

// 从起点到u，流量最大值为limit
int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0; // u->T的流量
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        int j = e[i];
        cur[u] = i; // 更新当前弧
        if (d[j] == d[u] + 1 && w[i]) {
            int t = find(j, min(w[i], limit - flow));
            if (!t) d[j] = -1; // 删点
            w[i] -= t, w[i ^ 1] += t, flow += t;
        }
    }
    return flow;
}

int dinic() {
    int max_flow = 0;
    while (bfs()) while (int flow = find(S, INF)) max_flow += flow;
    return max_flow;
}

int main() {
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c; 
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); // 初始流量为0，对于原图的残留网络，正向边容量为c-0=c，反向边容量为0+0=0
    }
    printf("%d\n", dinic());
    return 0;
}