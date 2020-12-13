// ST表可维护区间最值/区间gcd
int n, a[N];
int f[N][M]; // f[i][j]表示区间[i, i+2^j-1]区间的最大值
int Log2[N];

void ST_pre() {
    Log2[2] = 1;
    for (int i = 3; i < N; i++) Log2[i] = Log2[i >> 1] + 1;
    for (int i = 1; i <= n; i++) f[i][0] = a[i];
    for (int j = 1; j < M; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j-  1], f[i + (1 << j - 1)][j - 1]);
    }
}

int query(int l, int r) {
    int k = Log2[r - l + 1];
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}