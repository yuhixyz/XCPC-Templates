/* O(n+m) */
int n, m;
int h[N], e[M], ne[M] ,idx;
int color[N];

// 返回false染色失败，不是二分图
bool dfs(int u, int c) {
    color[u] = c;   // 将u染成c
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (!color[j]) { // 如果j未染色
            if (!dfs(j, 3 - c)) return false; // 染色失败
        } else if (color[j] == c) {
            return false; // 与现有颜色矛盾
        }
    }
    return true;
}

bool check() {
    for (int i = 1; i <= n; i++) {
        if (!color[i])
            if (!dfs(i, 1))
                return false;
    }
    return true;
}