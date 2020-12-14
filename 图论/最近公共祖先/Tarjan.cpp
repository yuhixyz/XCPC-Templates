#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

const int N = 10010, M = 2 * N;

int n, m;
int h[N], e[M], ne[M], w[M], idx;
int p[N], dist[N], st[N], res[M];
vector<PII> query[N];

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

int find(int x) {
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void tarjan(int u, int fa) {
    st[u] = 1; // 标记为正在搜的点
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        if (!st[j]) { // 还没搜过的点
            dist[j] = dist[u] + w[i];
            tarjan(j, u);
            p[j] = u;
        }
    }
    // 遍历u的所有查询
    for (auto item : query[u]) {
        int v = item.first, id = item.second;
        if (st[v] == 2) { // 已经搜完回溯的点, find(v)为u, v的LCA
            res[id] = dist[u] + dist[v] - 2 * dist[find(v)];
        }
    }
    st[u] = 2; // 标记为已经搜完回溯的点
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        query[a].push_back({b, i}); // 需要加双向询问
        query[b].push_back({a, i});
    }
    tarjan(1, -1);
    for (int i = 0; i < m; i++) printf("%d\n", res[i]);
    return 0;
}