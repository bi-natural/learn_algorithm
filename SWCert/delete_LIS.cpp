#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 100000;

int CASE;
int N;

int NV[MAX_N+1];

int LISET[MAX_N+1];
int xbegin, xend;

void dumpSet()
{
    printf("{ ");
    for (int j = xbegin; j < xend; j++)
        printf("%d ", LISET[j]);
    printf("}\n");
}

void findDeleteSet()
{
    LISET[0] = NV[0];
    xbegin = 0, xend = 1;

    printf("add %d { %d }\n", NV[0], NV[0]);

    for (int i = 1; i < N; ++i) {
        printf("add %d ", NV[i]);
        LISET[xend] = NV[i];
        if (NV[i] < LISET[xend-1]) {
            xend++;
            dumpSet();
            continue;
        }

        int lt;
        for (lt = xend-1; lt >= 0; --lt) {
            if (LISET[lt] > LISET[xend])
                break;
        }

        LISET[lt+1] = LISET[xend];
        dumpSet();
    }
}

int main()
{
    freopen("data/delete_LIS.txt", "r", stdin);

    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d\n", &N);
        for (int i = 0; i < N; ++i) {
            scanf("%d", &NV[i]);
        }

        memset(LISET, 0, sizeof(LISET));
        xbegin = xend = 0;

        findDeleteSet();

        printf("#%d %d\n", t, xend);
    }
    return 0;
}
