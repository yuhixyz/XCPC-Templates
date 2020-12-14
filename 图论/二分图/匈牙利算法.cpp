int n1, n2, m;
int h[N], e[M], ne[M], idx;
int match[N]; // match[j]:j号女生匹配的男生
/* 二分图最大匹配 O(nm)实际比较快 */
bool st[N];

void add(int a, int b) {
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

bool find(int x) {
    // 遍历x号男生看上的所有女生
    for (int i = h[x]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!st[j]) { // 防止重复匹配
            st[j] = true; // 标即为匹配过了
            if (match[j] == 0 || find(match[j])) { // 如果j号女生还没有匹配到男生或者她匹配到的男生可以找到下家
                match[j] = x; // 就把j匹配给x
                return true;
            }
        }
    }
    return false;
}

int calc() {
    int res = 0;
    for (int i = 1; i <= n1; i++) {
        memset(st, false, sizeof st);
        if (find(i)) res++;
    }
    return res;
}