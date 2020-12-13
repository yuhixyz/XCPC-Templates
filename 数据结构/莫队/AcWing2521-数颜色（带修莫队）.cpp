#include <bits/stdc++.h>

using namespace std;

const int N = 10010, M = 1000010;

int n, m, B;
int color[N], belong[N];
int qcnt, pcnt; // qcnt为询问编号，pcnt为操作的编号
struct Query {
    int id, l, r, ts; // id表示当前询问的编号，ts表示当前询问处于第ts次操作后，第ts+1操作前
    bool operator < (const Query &W) const {
        if (belong[l] != belong[W.l]) return belong[l] < belong[W.l];
        if (belong[r] != belong[W.r]) return belong[r] < belong[W.r];
        return ts < W.ts;
    }
} q[N];
struct Modify {
    int x, c; // 将下标为x的位置的颜色修改成c
} p[N];
int cnt[M], ans[N];

void build() {
    B = pow(n, 2.0 / 3);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / B + 1;
}

void add(int x, int &res) {
    if (++cnt[x] == 1) res++;
}

void del(int x, int &res) {
    if (--cnt[x] == 0) res--;    
}

// 将编号为ts的操作的影响作用到编号为i的询问
void modify(int ts, int i, int &res) {
    // 如果第ts次操作的位置在第i次询问的区间内部，就需要删除原来的颜色，再加上新颜色，以对答案造成影响
    if (p[ts].x >= q[i].l && p[ts].x <= q[i].r) {
        del(color[p[ts].x], res);
        add(p[ts].c, res);
    }
    // 上面只是修改cnt和res，实际的颜色修改，技巧，交换原来的颜色，和第ts次操作的颜色，这样下次需要撤销这次操作，相当于执行这次颜色被交换过的新操作。
    swap(color[p[ts].x], p[ts].c);    
}

int main() {
    scanf("%d%d", &n, &m);
    build();
    for (int i = 1; i <= n; i++) scanf("%d", &color[i]);
    for (int i = 0; i < m; i++) {
        char op[2];
        int l, r;
        scanf("%s%d%d", op, &l, &r);
        if (*op == 'Q') {
            ++qcnt;
            q[qcnt] = {qcnt, l, r, pcnt}; // 询问
        } else {
            p[++pcnt] = {l, r}; // 修改
        }
    }
    // 对于询问排序
    sort(q + 1, q + qcnt + 1);
    // 枚举每一个询问，初始下标区间为[l,r]为[1, 0]，为空，不同颜色个数res=0，处在第ts=0个操作之后，第ts+1=1个操作之前
    for (int i = 1, l = 1, r = 0, res = 0, ts = 0; i <= qcnt; i++) {
        // 将[l,r,ts]移动到[q[i].l, q[i].r, q[i].ts]
        while (r < q[i].r) add(color[++r], res);
        while (l > q[i].l) add(color[--l], res);
        while (r > q[i].r) del(color[r--], res);
        while (l < q[i].l) del(color[l++], res);
        while (ts < q[i].ts) modify(++ts, i, res); // 需要将ts+1~q[i].ts的操作造成的影响累加到答案上
        while (ts > q[i].ts) modify(ts--, i, res); // 需要消除q[i].ts+1~ts的操作对答案的影响
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= qcnt; i++) printf("%d\n", ans[i]);
    return 0;
}