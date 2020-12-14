/*
 * AcWing1282 搜索关键词
 * 输入：T组数据，给定n，然后n个单词，最后给一个字符串表示文章
 * 求有多少个单词（可以是相同的）在文章中出现
*/
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10010 * 50, M = 1000010;

int T, n;
int son[N][26], cnt[N], idx;
int ne[N];
char str[M];
int ans;
int q[N];

void insert(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++;
}

void build() {
    int hh = 0, tt = -1;
    for (int i = 0; i < 26; i++) {
        if (son[0][i]) q[++tt] = son[0][i];
    }
    while (hh <= tt) {
        int t = q[hh++];
        for (int i = 0; i < 26; i++) {
            if (!son[t][i]) son[t][i] = son[ne[t]][i];
            else {
                ne[son[t][i]] = son[ne[t]][i];
                q[++tt] = son[t][i];
            }
        }
    }
}

void init() {
    memset(ne, 0, sizeof ne);
    idx = 0;
    memset(cnt, 0, sizeof cnt);
    memset(son, 0, sizeof son);
}

void solve() {
    init();
    cin >> n;
    for (int i = 0; i < n; i++) {
        scanf("%s", str);
        insert(str);
    }
    build();
    scanf("%s", str);
    ans = 0;
    for (int i = 0, j = 0; str[i]; i++) {
        int u = str[i] - 'a';
        j = son[j][u];
        int k = j;
        while (k) {
            ans += cnt[k];
            cnt[k] = 0;
            k = ne[k];
        }
    }
    cout << ans << endl;
}

int main() {
    cin >> T;
    while (T--) solve();
    return 0;
}