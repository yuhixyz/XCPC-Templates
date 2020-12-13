/*
 * belong[i]表示下标i所属于的块编号
 * B表示每一块的大小,sz表示一共有多少块
 * L[i],R[i]分别表示块i的左闭边界和右闭边界
*/
int n, B, sz;
int belong[N], L[N], R[N];

void build() {
    B = sqrt(n), sz = (n - 1) / B + 1;
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / B + 1;
    for (int i = 1; i <= sz; i++) L[i] = (i - 1) * B + 1, R[i] = L[i] + B - 1;
    R[sz] = n;
}