// 注意树状数组不能处理下标0开始
// 一维
int c[N];

inline int lowbit(int x) {
    return x & -x;
}

int add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) c[i] += y;
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += c[i];
    return res;
}

// 二维
LL c[N][N];
 
inline int lowbit(int x) {
    return x & -x;
}
 
void add(int x, int y, LL v) {
    for (int i = x; i <= n;i += lowbit(i))
        for (int j = y; j <= m;j += lowbit(j))
            c[i][j] += v;
}
 
LL query(int x, int y) {
    LL ans = 0;
    for (int i = x; i; i -= lowbit(i))
        for (int j = y; j; j -= lowbit(j))
            ans += c[i][j];
    return ans;
}