#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 500;
const int MAX_M = 2500;
const int MAX_W = 200;

int CASE;
int N, M, W;

int g[MAX_N+1][MAX_N+1];
int w[MAX_W][2][2];

int main()
{
    freopen("data/wormhole.dat", "r", stdin);

    scanf("%d\n", &CASE);
    for (int t = 1; t <= CASE; ++t) {
        scanf("%d %d %d\n", &N, &M, &W);

        memset(g, 0, sizeof(g));
        for (int i = 0; i < M; ++i) {
            int d[3];

            scanf("%d %d %d\n", &d[0], &d[1], &d[2]);
            g[d[0]][d[1]] = d[2];
            g[d[1]][d[0]] = d[2];
        }

        memset(w, 0, sizeof(w));
        for (int i = 0; i < W; ++i) {
            int d[3];

            scanf("%d %d %d\n", &d[0], &d[1], &d[2]);
            w[i][d[0]]
        }

    }
}