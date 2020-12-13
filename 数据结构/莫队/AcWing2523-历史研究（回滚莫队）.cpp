#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100010;

int n, m, B, sz;
int belong[N], L[N], R[N], a[N];
struct Query {
    int id, l, r;
    bool operator < (const Query &W) const {
        if (belong[l] != belong[W.l]) return belong[l] < belong[W.l];
        return r < W.r;
    }
} q[N];
vector<int> alls;
int cnt[N];
LL ans[N];

void build() {
    B = sqrt(n), sz = (n - 1) / B + 1;
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / B + 1;
    for (int i = 1; i <= sz; i++) L[i] = (i - 1) * B + 1, R[i] = L[i] + B - 1;
    R[sz] = n;
}

int find(int x) {
    return lower_bound(alls.begin(), alls.end(), x) - alls.begin();
}

void add(int x, LL &res) {
    cnt[x]++;
    res = max(res, (LL)cnt[x] * alls[x]);
}

int main() {
    scanf("%d%d", &n, &m); build();
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        alls.push_back(a[i]);
    }
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());
    for (int i = 1; i <= n; i++) a[i] = find(a[i]);
    for (int i = 0, l, r; i < m; i++) {
        scanf("%d%d", &l, &r);
        q[i] = {i, l, r};
    }
    sort(q, q + m);
    for (int i = 0; i < m; ) {
        int j = i;
        while (j + 1 < m && belong[q[i].l] == belong[q[j + 1].l]) j++;
        // 此时[i,j]区间内的所有询问的左端点属于同一块，右端点递增
        // 暴力求块内（左右端点在同一块内的询问）
        while (i <= j && belong[q[i].l] == belong[q[i].r]) {
            LL res = 0;
            for (int k = q[i].l; k <= q[i].r; k++) add(a[k], res);
            ans[q[i].id] = res;
            // 清空cnt
            for (int k = q[i].l; k <= q[i].r; k++) cnt[a[k]]--;
            i++;
        }
        // 求跨块，分为两部分：左边第一个块内的部分和它右边块的部分
        LL res = 0;
        int block_id = belong[q[i].l];
        int r = R[block_id], l = r + 1; // 莫队区间初始化
        // 右端点递增，只存在add操作，左端点先初始化到block_id块的右端点，然后向左使用add操作
        while (i <= j) {
            while (r < q[i].r) add(a[++r], res);
            LL tmp = res; // 备份
            while (l > q[i].l) add(a[--l], res);
            ans[q[i].id] = res;
            // 清空左边部分对于cnt[]的影响，且让l回到初始位置
            while (l <= R[belong[q[i].l]]) cnt[a[l++]] -- ;
            res = tmp;
            i++;
        }
        // 清空cnt，对于每一块只会执行一次，复杂度为n根号n
        memset(cnt, 0, sizeof cnt);
    }
    for (int i = 0; i < m; i++) printf("%lld\n", ans[i]);
    return 0;
}
