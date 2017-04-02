/*
 * Coin Exchange 
 *
 --
 최소 동전단위 이후부터 D[i]를 계산하되, 전체 동전단위에 대해 D[i-A[i]]의 값에 1를 더해
 액수를 만들수 있으면 그때 업데이 트
 
 D[i] = min(D[i-A[j]])+1 (for all j, s.t. A[j] ≤ i)
 
 --
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

#define DEBUG 

const int MAX_N = 500;
const int MAX_C = 64000;

int N, W;
int coins[MAX_N + 9];

int dp[MAX_C + 1];
int dph[MAX_C + 1];

int COIN(int w)
{
	/* 초기값 coin 1개로 만들수 있는 돈의 액수 */
	dp[0] = 0;

#ifdef DEBUG
	for (int i = 1; i <= w; ++i) {
		printf("%5d", i);
	}
	printf("\n");
	for (int i = 1; i <= w; ++i) {
		printf("%5d", dp[i]);
	}
	printf("\n");
#endif
	for (int i = 1; i <= w; ++i) {
		int& v = dp[i];

		v = 1e10;

		// for each coin type
		for (int j = 1;j <= N ; ++j) {
			if (i >= coins[j]) {
				int preIdx = i - coins[j];

				if (v > dp[preIdx]) {
					v = dp[preIdx] + 1;
					dph[i] = j - preIdx;
#ifdef DEBUG
					printf("-- %d : update from j (%d) --> value = %d\n", i, preIdx, v);
#endif
				}
			}
		}
	}

#ifdef DEBUG
	for (int i = 1; i <= w; ++i) {
		printf("%5d", i);
	}
	printf("\n");
	for (int i = 1; i <= w; ++i) {
		printf("%5d", dp[i]);
	}
	printf("\n");
#endif
	return dp[w];
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\coin.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i) {
		scanf("%d", coins + i);
	}

	scanf("%d", &W);

	sort(coins + 1, coins + N + 1);
#ifdef DEBUG
	printf("coins[%d]\n", N);
	for (int i = 1; i <= N; ++i)
		printf("%3d", i);
	printf("\n");
	for (int i = 1; i <= N; ++i)
		printf("%3d", coins[i]);
	printf("\n");
	printf("w = %d\n", W);
#endif

	memset(dp, -1, sizeof(dp));
	memset(dph, 0, sizeof(dph));

	int result = COIN(W);

	printf("%d\n", result);
}
