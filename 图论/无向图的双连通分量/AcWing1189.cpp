/* 
 * AcWing1181 电力 
 * 给定一个由n个点m条边构成的无向图，
 * 求出该图删除一个点之后，连通块最多有多少。 
 * 点的双连通分量模板
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 10010, M = 30010;

int n, m;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], timestamp;
int s; // 删除结点u后，u所在连通块最多分裂出的连通块数目

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u, int root) {
    dfn[u] = low[u] = ++timestamp;
    int cnt = 0; // 删掉u后，u分裂的子树数目
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j, root);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) cnt++;
        } else {
            low[u] = min(low[u], dfn[j]);
        }
    }
    // 只要u不是根节点，而且u有子树，那么删掉u后，还要算上u的父亲所在连通块
    if (u != root) cnt++;
    s = max(s, cnt);
}

int main() {
    while (scanf("%d%d", &n, &m), n || m) {
        memset(h, -1, sizeof h);
        idx = timestamp = 0;
        memset(dfn, 0, sizeof dfn);
        while (m--) {
            int a, b;
            cin >> a >> b;
            a++, b++;
            add(a, b), add(b, a);
        }
        s = 0;
        int cnt = 0; // 统计删点前连通块的个数
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i, i);
                cnt++;
            }
        }
        cout << cnt + s - 1 << endl;
    }
    return 0;
}