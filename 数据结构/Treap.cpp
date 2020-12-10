#include <bits/stdc++.h>

using namespace std;

const int N = 100010, INF = 1e8;

int n;
struct Node {
    int l, r;
    int key, val;
    int cnt, sz;
} tr[N];
int root, idx;

int new_node(int key) {
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].sz = 1;
    return idx;
}

void pushup(int p) {
    tr[p].sz = tr[tr[p].l].sz + tr[tr[p].r].sz + tr[p].cnt;
}

void build() {
    new_node(-INF), new_node(INF);
    root = 1, tr[1].r = 2;
    pushup(root);
}

void RR(int &p) {
    int q = tr[p].l;
    tr[p].l = tr[q].r, tr[q].r = p, p = q;
    pushup(tr[p].r), pushup(p);
}

void LR(int &p) {
    int q = tr[p].r;
    tr[p].r = tr[q].l, tr[q].l = p, p = q;
    pushup(tr[p].l), pushup(p);
}

void insert(int &p, int key) {
    if (!p) p = new_node(key);
    else if (tr[p].key == key) tr[p].cnt++;
    else if (tr[p].key > key) {
        insert(tr[p].l, key);
        if (tr[tr[p].l].val > tr[p].val) RR(p);
    } else {
        insert(tr[p].r, key);
        if (tr[tr[p].r].val > tr[p].val) LR(p);
    }
    pushup(p);
}

void remove(int &p, int key) {
    if (!p) return;
    if (tr[p].key == key) {
        if (tr[p].cnt > 1) tr[p].cnt--;
        else if (tr[p].l || tr[p].r) {
            if (!tr[p].r || tr[tr[p].l].val > tr[tr[p].r].val) {
                RR(p);
                remove(tr[p].r, key);
            } else {
                LR(p);
                remove(tr[p].l, key);
            }
        } else {
            p = 0;
        }
    } else if (tr[p].key > key) {
        remove(tr[p].l, key);
    } else {
        remove(tr[p].r, key);
    }
    pushup(p);
}

int get_rank_by_key(int p, int key) {
    if (!p) return 0; // never occur in this problem
    if (tr[p].key == key) return tr[tr[p].l].sz + 1;
    if (tr[p].key > key) return get_rank_by_key(tr[p].l, key);
    return tr[tr[p].l].sz + tr[p].cnt + get_rank_by_key(tr[p].r, key);
}

int get_key_by_rank(int p, int rank) {
    if (!p) return INF; // never occur in this problem
    if (tr[tr[p].l].sz >= rank) return get_key_by_rank(tr[p].l, rank);
    if (tr[tr[p].l].sz + tr[p].cnt >= rank) return tr[p].key;
    return get_key_by_rank(tr[p].r, rank - tr[tr[p].l].sz - tr[p].cnt);
}

// find max that smaller than key
int get_prev(int p, int key) {
    if (!p) return -INF;
    if (tr[p].key >= key) return get_prev(tr[p].l, key);
    return max(tr[p].key, get_prev(tr[p].r, key));
}

// find min that bigger than key
int get_next(int p, int key) {
    if (!p) return INF;
    if (tr[p].key <= key) return get_next(tr[p].r, key);
    return min(tr[p].key, get_next(tr[p].l, key));
}

int main() {
    build();
    cin >> n;
    while (n--) {
        int op, x;
        cin >> op >> x;
        if (op == 1) insert(root, x);
        else if (op == 2) remove(root, x);
        else if (op == 3) printf("%d\n", get_rank_by_key(root, x) - 1); // 注意之前插入了-INF的哨兵
        else if (op == 4) printf("%d\n", get_key_by_rank(root, x + 1)); 
        else if (op == 5) printf("%d\n", get_prev(root, x));
        else printf("%d\n", get_next(root, x));
    }
    return 0;
}