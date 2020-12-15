/* 
 * AcWing396 矿场搭建 
 * 点的双连通分量、割点模板
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1010, M = 1010;

int n, m, Case;
int h[N], e[M], ne[M], idx;
int dfn[N], low[N], ts;
vector<int> dcc[N]; // 存每一个点的双连通分量的所有点编号
int dcc_cnt; // 点的双连通分量编号
bool cut[N]; // 是否为割点
int stk[N], top;
int root;

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ts;
    stk[++top] = u;
    if (u == root && h[u] == -1) {
        dcc_cnt ++ ;
        dcc[dcc_cnt].push_back(u);
        return;
    }
    int cnt = 0;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (dfn[u] <= low[j]) {
                cnt++ ;
                if (u != root || cnt > 1) cut[u] = true;
                ++dcc_cnt;
                int v;
                do {
                    v = stk[top--];
                    dcc[dcc_cnt].push_back(v);
                } while (v != j);
                dcc[dcc_cnt].push_back(u);
            }
        } else low[u] = min(low[u], dfn[j]);
    }
}

void init() {
    for (int i = 1; i <= dcc_cnt; i ++ ) dcc[i].clear();
    idx = n = ts = top = dcc_cnt = 0;
    memset(h, -1, sizeof h);
    memset(dfn, 0, sizeof dfn);
    memset(cut, 0, sizeof cut);
}

int main() {
    while (cin >> m, m) {
        init();
        while (m -- ) {
            int a, b;
            cin >> a >> b;
            n = max(n, a), n = max(n, b);
            add(a, b), add(b, a);
        }
        for (root = 1; root <= n; root++) {
            if (!dfn[root]) tarjan(root);
        }
        int res = 0;
        long long num = 1;
        for (int i = 1; i <= dcc_cnt; i++) {
            int cnt = 0;
            for (int j = 0; j < dcc[i].size(); j++) {
                if (cut[dcc[i][j]]) cnt ++ ;
            }
            if (cnt == 0) {
                if (dcc[i].size() > 1) {
                    res += 2;
                    num *= dcc[i].size() * (dcc[i].size() - 1) / 2;
                } else res ++ ;
            }  else if (cnt == 1) {
                res++;
                num *= dcc[i].size() - 1;
            }
        }
        printf("Case %d: %d %llu\n", ++Case, res, num);
    }
    return 0;
}