/* AcWing2179 圆桌问题 */
#include <bits/stdc++.h>

using namespace std;

const int N = 500, M = 90010, INF = 1e9;

int m, n, S, T, tot;
int h[N], e[M], ne[M], w[M], idx;
int q[N], d[N], cur[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() {
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
                if (j == T) return true;
            }
        }
    }
    return false;
}

int find(int u, int limit) {
    if (u == T) return limit;
    int flow = 0;
    for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
        int j = e[i];
        cur[u] = i;
        if (d[j] == d[u] + 1 && w[i]) {
            int t = find(j, min(w[i], limit - flow));
            if (!t) d[j] = -1;
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
    cin >> m >> n;
    S = 0, T = m + n + 1;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int x; scanf("%d", &x);
        tot += x, add(S, i, x);
    }
    for (int i = 1; i <= n; i++) {
        int x; scanf("%d", &x);
        add(m + i, T, x);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            add(i, m + j, 1);
        }
    }
    if (tot != dinic()) return 0 * puts("0");
    puts("1");
    for (int i = 1; i <= m; i++) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            if (k > m && !w[j]) printf("%d ", k - m); 
        }
        puts("");
    }
    return 0;
}