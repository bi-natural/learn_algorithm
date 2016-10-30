#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>


using namespace std;

const int MAX_N = 5000;
const int MAX_K = 5000;
const int MAX_C = 2;

int CASE;
int N, K, C;
int NV[MAX_N+1];

int cache[MAX_N+1][MAX_K+1][3];
int nextMax[MAX_N+1];
int nextCheeta[MAX_N+1];

int findNextMax(int n)
{
    if (n == N) { return nextMax[n] = 0; }
    if (nextMax[n] != -1) { return nextMax[n]; }

    int& result = nextMax[n];
    result = n;

    int start_lope = NV[n];
    int next_max_lope = 0;
    for (int i = 1 ; i <= start_lope && n+i < N; ++i)
        if (NV[n+i] >= next_max_lope) {
            result = n+i;
            next_max_lope = NV[n+i];
        }
    return result;
}

int findNextCheeta(int n) 
{
    if (nextCheeta[n] != -1) { return nextCheeta[n]; }

    int& max_i = nextCheeta[n];
    max_i = 0;

    for ( int i = 1; n + i < N; ++i) {
        if (NV[n+i] >= i) {
            max_i = n+i;
        }
    }
    return max_i;
}

int findMaxLength(int n, int k, int c)
{
//printf("CALL: n=%d, k=%d, c=%d\n", n, k, c);
    if (n == N || k == K) { return cache[N][K][C] = n; }

    int& result = cache[n][k][c];
    if (result != -1) return result;

    result = 0;
    if (k < K) {
        // 그냥 건너뜀
        int nIndex = findNextMax(n);
//printf("[%d]: Goto %d\n", n, nIndex);
        result = max(result, findMaxLength(nIndex, k + 1, c));

        if (c < C) {
            int nCheeta = findNextCheeta(n +1);
//printf("[%d]: Cheeta %d\n", n, nCheeta);
            if (nCheeta > n) {
                result = max(result, findMaxLength(nCheeta, k, c + 1));
            }
        }
    }
//printf("[%d]: Result %d\n", n, result);    
    return result;
}

int main()
{
    freopen("data/tarjan.txt", "r", stdin);

    scanf("%d", &CASE);
    for (int t =1; t <= CASE; ++t) {
        scanf("%d %d %d", &N, &K, &C);

        memset(NV, 0, sizeof(NV));
        for (int i = 0; i < N; ++i) {
            scanf("%d", &NV[i]);
//            printf("%d ", NV[i]);
        }
//        printf("\n%d %d %d\n", N, K, C);

        memset(cache, -1, sizeof(cache));
        memset(nextMax, -1, sizeof(nextMax));
        memset(nextCheeta, -1, sizeof(nextCheeta));

        int result = findMaxLength(0, 0, 0);
        printf("#%d %d\n", t, result+1);
    }
}