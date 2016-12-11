/*
 * http://codedoc.tistory.com/m/9
 *
 */

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#include <vector>

const int MAX_N = 100000;

long long int arr[MAX_N+1], tree[2][MAX_N+1];
int n, q;

#define LSB(s)  ((s) & (-s))

void add(int type, int i, int x) {
    for (; i <= n; i += LSB(i))
        tree[type][i] += x;
}

long long sum(int type, int i) {
    int d = i;
    long long s = 0;
    for (; i > 0; i -= LSB(i))
        s += tree[type][i];
    printf("sum(%d, %d) = %lld\n", type, d, s);
    return s;
}

void dump()
{
    printf("t[0] = ");
    for (int i = 1; i <= n; ++i) {
        printf("%lld, ", tree[0][i]);
    }
    printf("\n");
    printf("t[1] = ");
    for (int i = 1; i <= n; ++i) {
        printf("%lld, ", tree[1][i]);
    }
    printf("\n");
}

int main()
{
    freopen("bit2.txt", "r", stdin);
    scanf("%d %d", &n, &q);
    arr[0] = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &arr[i]);
        arr[i] += arr[i-1];
    }

    char ch;
    for (int i = 1, a, b, c; i <= q; ++i) {
        scanf(" %c", &ch);
        if (ch == 'C') {
            scanf("%d %d %d", &a, &b, &c);

            add(0, a, c);
            add(0, b, -c);
            add(1, a, -a*c + c);
            add(1, b, b*c);
            dump();
        }
        else {
            scanf("%d %d", &a, &b);
            printf("#%d %lld\n",  i, arr[b] - arr[a-1] +
                sum(0, b) * b + sum(1, b) - sum(0, a-1)*(a-1) + sum(1, a-1)
        );
        }
    }
}
