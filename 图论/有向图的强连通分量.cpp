/*
 * AcWing1174 受欢迎的牛
 * 求能被其他所有点到达的点有多少个
 * Tarjan缩点后，统计出度为0的点的个数
 * 个数大于1则答案为0，个数为1则答案为该scc的大小
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 10010, M = 50010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int dout[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
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
    while (m--) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = h[i]; ~j; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) dout[a]++;
        }
    }
    int cnt = 0, res = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!dout[i]) {
            cnt++;
            res = sz[i];
            if (cnt > 1) {
                res = 0;
                break;
            }
        }
    }
    printf("%d\n", res);
    return 0;
}