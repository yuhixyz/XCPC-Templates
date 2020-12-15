/* AcWing368 银河 */
#include <bits/stdc++.h>

using namespace std;

const int N = 100010, M = 600010;

int n, m;
int h[N], hs[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], sz[N], scc_cnt;
int dist[N];

void add(int h[], int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u, in_stk[u] = true;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int v;
        do {
            v = stk[top--];
            in_stk[v] = false;
            id[v] = scc_cnt;
            sz[scc_cnt]++;
        } while (v != u);
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    while (m--) {
        int a, b, t;
        scanf("%d%d%d", &t, &a, &b); // 顺序错了调到自闭
        if (t == 1) add(h, a, b, 0), add(h, b, a, 0);
        else if (t == 2) add(h, a, b, 1);
        else if (t == 3) add(h, b, a, 0);
        else if (t == 4) add(h, b, a, 1);
        else if (t == 5) add(h, a, b, 0);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    bool flag = true; // 判是否存在正环
    for (int i = 1; i <= n; i++) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) add(hs, a, b,w[j]);
            else if (w[j] > 0) {
                flag = false;
                break;
            }
        }
        if (!flag) break;
    }
    if (!flag) puts("-1");
    else { // 按拓扑序求最长路
        for (int i = scc_cnt; i; i--) {
            if (!dist[i]) dist[i] = 1;
            for (int j = hs[i]; ~j; j = ne[j]) {
                int k = e[j];
                dist[k] = max(dist[k], dist[i] + w[j]);
            }
        }
        long long res = 0;
        for (int i = 1; i <= scc_cnt; i++) res += 1ll * dist[i] * sz[i];
        cout << res << endl;
    }
    return 0;
}