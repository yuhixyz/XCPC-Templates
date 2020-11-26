#include <bits/stdc++.h>

using namespace std;

const int N = 1010, M = 20010, INF = 1e9;

int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int q[N], f[N]; // f[i]表示以i结尾的增广路径的流量（即路径上容量的最小值）
int pre[N]; // pre[i]表示i的前驱边的编号（即指向i的边）

void add(int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx++;
}

bool bfs() { // 判断残留网络是否存在增广路（即从S到T存在边全大于0的路径）
    int hh = 0, tt = -1;
    memset(st, false, sizeof st);
    q[++tt] = S, st[S] = true, f[S] = INF;
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (!st[j] && w[i]) {
                q[++tt] = j;
                st[j] = true;
                pre[j] = i; // 记录j的前驱边
                f[j] = min(f[t], w[i]);
                if (j == T) return true; // j是终点，即找到了增广路，此时增广路的流量即f[T]
            }
        }
    }
    return false; // 残留网络不存在增广路，那么此时原图的可行流流量就是最大流
}

int EK() {
    int flow = 0;
    while (bfs()) { // 如果残留网络存在增广路f'，就将他的流量加到原网络的流量上
        flow += f[T];
        for (int i = T; i != S; i = e[pre[i] ^ 1]) { // 更新残留网络
            w[pre[i]] -= f[T], w[pre[i] ^ 1] += f[T];
        }
    }
    return flow; // 最大流
}

int main() {
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    while (m--) {
        int a, b, c; 
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c); // 初始流量为0，对于原图的残留网络，正向边容量为c-0=c，反向边容量为0+0=0
    }
    printf("%d\n", EK());
    return 0;
}