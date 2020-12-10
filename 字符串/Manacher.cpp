/* O(n)求字符串s的最大回文长度 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 2000010;

int n, m, Case;
char s[N], str[N]; // s为原串,str为插入分隔符后的串
int p[N]; // p[i]为str中以下标i为中心的最大回文半径
// p[i]-1为s中以i为回文中心的最大回文长度

void manacher() {
    int rt = 0, mid = 0;
    int res = 0;
    for (int i = 1; i <= m; i++) {
        p[i] = i < rt ? min(p[2 * mid - i], rt - i) : 1;
        while (str[i + p[i]] == str[i - p[i]]) p[i]++;
        if (i + p[i] > rt) {
            rt = i + p[i];
            mid = i;
        }
        res = max(res, p[i] - 1);
    }
    printf("Case %d: %d\n", ++Case, res);
}

int main() {
    str[0] = '!', str[1] = '#'; /* str[0]为哨兵 */
    while (scanf("%s", s), s[0] != 'E') {
        n = strlen(s);
        for (int i = 0; i < n; i++) {
            str[i * 2 + 2] = s[i];
            str[i * 2 + 3] = '#';
        }
        m = n * 2 + 1;
        str[m + 1] = '@';  /* 哨兵 */   
        manacher();
    }
    return 0;
}
