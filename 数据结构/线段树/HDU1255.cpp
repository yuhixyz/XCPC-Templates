#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int T, n;
struct Segment {
    double x, y1, y2;
    int k;
    bool operator < (const Segment &W) const {
        return x < W.x;
    }
} seg[N];
struct Node {
    int l, r, cnt; // cnt表示[l,r]区间被完全覆盖的次数
    double len1, len2; // len1表示线段树区间[l,r]中cnt>0的区间合并后的长度，len2对应cnt>1
} tr[N << 2]; 
vector<double> ys;

int find(double y) {
    return lower_bound(ys.begin(), ys.end(), y) - ys.begin();
}

void pushup(int u) {
    // 更新len1
    if (tr[u].cnt > 0) {
        tr[u].len1 = ys[tr[u].r + 1] - ys[tr[u].l];
    } else if (tr[u].l == tr[u].r) {
        tr[u].len1 = 0;
    } else {
        tr[u].len1 = tr[u << 1].len1 + tr[u << 1 | 1].len1;
    }
    // 更新len2
    if (tr[u].cnt > 1) {
        tr[u].len2 = ys[tr[u].r + 1] - ys[tr[u].l];
    } else if (tr[u].l == tr[u].r) {
        tr[u].len2 = 0;
    } else {
        if (tr[u].cnt == 1) { // 被完全覆盖了1次
            // 如果子区间有恰好被覆盖至少1次的，那么合在一起就是至少覆盖2次的面积了
            tr[u].len2 = tr[u << 1].len1 + tr[u << 1 | 1].len1; // 加上子区间至少覆盖1次的面积
        } else { // cnt=0
            tr[u].len2 = tr[u << 1].len2 + tr[u << 1 | 1].len2;
        }
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
    for (cin >> T; T--; ) {
        cin >> n;
        ys.clear();
        for (int i = 0; i < n; i++) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            seg[i * 2] = {x1, y1, y2, 1};
            seg[i * 2 + 1] = {x2, y1, y2, -1};
            ys.push_back(y1), ys.push_back(y2);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        build(1, 0, ys.size() - 2);
        sort(seg, seg + n * 2);
        double res = 0;
        for (int i = 0; i < n * 2; i++){
            if (i) res += tr[1].len2 * (seg[i].x - seg[i - 1].x);
            int l = find(seg[i].y1), r = find(seg[i].y2) - 1;
            modify(1, l, r, seg[i].k);
        }
        printf("%.2lf\n", res);
    }
    return 0;
}
