#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, m;
int a[N], cnt[N], s[N][2], sum[N][2];
int belong[N], L[N], R[N], B, sz;
struct Query {
    int id, l, r, a, b;
    bool operator < (const Query &W) const {
        if (belong[l] != belong[W.l]) return belong[l] < belong[W.l];
        return r < W.r;
    }
} q[N];
int ans[N][2];

void build() {
	B = sqrt(n), sz = (n - 1) / B + 1;
	for (int i = 1; i <= n; i++) belong[i] = (i - 1) / B + 1;
	for (int i = 1; i <= sz; i++) L[i] = (i - 1) * B + 1, R[i] = L[i] + B - 1;
	R[sz] = n;
}

void add(int x) {
    x = a[x];
    cnt[x]++;
    s[x][0]++, sum[belong[x]][0]++;
    if (cnt[x] == 1) s[x][1]++, sum[belong[x]][1]++;
}

void del(int x) {
    x = a[x];
    cnt[x]--;
    s[x][0]--, sum[belong[x]][0]--;
    if (cnt[x] == 0) s[x][1]--, sum[belong[x]][1]--;
}

int ask(int l, int r, int type) {
    if (belong[l] == belong[r]) {
        int res = 0;
        for (int i = l; i <= r; i++) res += s[i][type];
        return res;
    }
    int res = 0;
    for (int i = l; i <= R[belong[l]]; i++) res += s[i][type];
    for (int i = belong[l] + 1; i < belong[r]; i++) res += sum[i][type];
    for (int i = L[belong[r]]; i <= r; i++) res += s[i][type];
    return res;
}

int main() {
    scanf("%d%d", &n, &m); build();
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) {
        int l, r, a, b;
        scanf("%d%d%d%d", &l, &r, &a, &b);
        q[i] = {i, l, r, a, b};
    }
    sort(q, q + m);
    for (int i = 0, l = 1, r = 0; i < m; i++) {
        while (r < q[i].r) add(++r);
        while (l > q[i].l) add(--l);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        ans[q[i].id][0] = ask(q[i].a, q[i].b, 0);
        ans[q[i].id][1] = ask(q[i].a, q[i].b, 1);
    }
    for (int i = 0; i < m; i++) printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}