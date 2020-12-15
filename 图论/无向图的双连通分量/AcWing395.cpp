/*
 * AcWing395 冗余路径
 * 给定一个无向图，求最少添加几条无向边，能使得原图变成一个边的双连通分量。
 * Tarjan求双连通分量，统计缩点后度数为1的点的个数cnt。
 * 结论：最少再添加cnt/2上取整条无向边。
 * 边的双连通分量、桥模板
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 5010, M = 20010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], tt;
int id[N], dcc_cnt;
int d[N];
bool bridge[M];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

// in_edge表示到u的入边
void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++timestamp;
    stk[++tt] = u;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, i);
            low[u] = min(low[u], low[j]);
            if (dfn[u] < low[j]) { // j无法走到u
                bridge[i] = bridge[i ^ 1] = true;
            }
        } else if (i != (in_edge ^ 1)) { // 不是反向边
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        ++dcc_cnt;
        int v;
        do {
            v = stk[tt--];
            id[v] = dcc_cnt;
        } while (v != u);
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    tarjan(1, -1);
    for (int i = 0; i < idx; i++) { // 遍历所有边
        if (bridge[i]) d[id[e[i]]]++;
    }
    int cnt = 0;
    for (int i = 1; i <= dcc_cnt; i++) {
        if (d[i] == 1) cnt++;
    }
    cout << (cnt + 1) / 2 << endl;
    return 0;
}