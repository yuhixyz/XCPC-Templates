int n, m;
int d[N][N];

void init() {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j) d[i][j] = INF;
}

void floyd() {
    for (int k = 1; k <= n ; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}