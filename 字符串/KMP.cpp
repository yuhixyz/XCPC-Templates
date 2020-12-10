/* 求出模板串P在模式串S中所有出现的位置的起始下标 */
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 10010, M = 100010;

int n, m; // n,m分别为p,s的长度
char p[N], s[M];
int ne[N]; // ne[i]表示以i结尾的真后缀能够匹配前缀的最大长度

int main() {
    cin >> n >> p + 1 >> m >> s + 1;
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && p[i] != p[j + 1]) j = ne[j];
        if (p[i] == p[j + 1]) j++;
        ne[i] = j;
    }
    for (int i = 1, j = 0; i <= m; i++) {
        while (j && (s[i] != p[j + 1])) j = ne[j];
        if (s[i] == p[j + 1]) j++;
        if (j == n) { // 匹配完成
            printf("%d ", i - 1 - n + 1);
            j = ne[j];
        }
    }
    return 0;
}