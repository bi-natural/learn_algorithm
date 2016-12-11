/*
 * http://codedoc.tistory.com/m/9
 *
 */

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#include <vector>

const int MAX_N = 100000;

int tree[MAX_N+1];
int n, q;

#define LSB(s)  ((s) & (-s))

void add(int i, int x) {
    for (; i <= n; i += LSB(i))
        tree[i] += x;
}

int sum(int i) {
    int d = i;
    int s = 0;
    for (; i > 0; i -= LSB(i))
        s += tree[i];
    printf("sum(%d) = %d\n", d, s);
    return s;
}

int main()
{
    freopen("bit1.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    for (int i = 1, a; i <= n; ++i) {
        scanf("%d", &a);
        add(i, a);
    }

    char ch;
    for (int i = 1, a, b; i <= q; ++i) {
        scanf(" %c %d %d", &ch, &a, &b);
        if (ch == 'C') {
            add(a, b);
        }
        else {
            printf("#%d %d\n", i, sum(b) - sum(a-1));
        }
    }
}
