#include <bits/stdc++.h>

using namespace std;

const int N = 200010;

int n, Case;
struct Segment {
    double x, y1, y2;
    int k;
    bool operator < (const Segment &W) const {
        return x < W.x;
    }
} seg[N];
// 线段树的每一个叶子结点（假设下标为i），表示一个区间[y_i, y_{i+1}]
struct Node {
    int l, r, cnt; // cnt表示[l,r]区间被完全覆盖的次数，cnt>0就表示要算上[l,r]这一整段，其表示实际的区间为[ys[l],ys[r+1]]
    double len; // len表示当前线段树的区间[l,r]内，cnt>0（即被覆盖的实际区间）的合并长度之和。
} tr[N << 2]; // 比如 y1, y2, y3 离散化后为k_y1,k_y2,k_y3。其区间[k_y1,k_y2],[k_y1,k_y2],[k_y2,k_y3]是线段树中的3个叶子结点。
vector<double> ys;

int find(double y) {
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}

void pushup(int u) {
    if (tr[u].cnt) {
        tr[u].len = ys[tr[u].r + 1] - ys[tr[u].l];
    } else if (tr[u].l != tr[u].r) {
        tr[u].len = tr[u << 1].len + tr[u << 1 | 1].len;
    } else {
        tr[u].len = 0;
    }
}

void build(int u, int l, int r) {
    tr[u] = {l, r, 0, 0};
    if (l == r) return;
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}

void modify(int u, int l, int r, int k) {
    if (tr[u].l >= l && tr[u].r <= r) {
        tr[u].cnt += k;
        pushup(u);
    } else {
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(u << 1, l, r, k);
        if (r > mid) modify(u << 1 | 1, l, r, k);
        pushup(u);
    }
}

int main() {
    while (cin >> n, n) {
        ys.clear();
        for (int i = 0; i < n; i ++ ) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[i * 2] = {x1, y1, y2, 1};
            seg[i * 2 + 1] = {x2, y1, y2, -1};
            ys.push_back(y1), ys.push_back(y2);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        build(1, 0, ys.size() - 2); // 共ys.size()个y，那么相邻之间就有ys.size()-1个区间，就有ys.size()-1个线段树的叶子节点。
        sort(seg, seg + n * 2);
        double res = 0;
        for (int i = 0; i < n * 2; i++){
            if (i) res += tr[1].len * (seg[i].x - seg[i - 1].x);
            int l = find(seg[i].y1), r = find(seg[i].y2) - 1;
            // 右端点注意要减去1，假设实际区间为[L,R]，那么对应线段树中的区间就是[L,R-1]
            modify(1, l, r, seg[i].k);
        }
        printf("Test case #%d\n", ++Case);
        printf("Total explored area: %.2lf\n\n", res);
    }
    return 0;
}
