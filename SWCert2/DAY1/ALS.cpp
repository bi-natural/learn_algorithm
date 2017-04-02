/* 
 * Assembly Line Scheduling 
 *
 --
 매 스텝마다 최저값들을 선택하여 최종라인까지 이동 
 --
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 300000;
const int MAX_H = 200;

int N;
int e1, e2, x1, x2;
int S1[MAX_N + 1];
int S2[MAX_N + 1];
int T1[MAX_N + 1];
int T2[MAX_N + 1];

int dp[MAX_N + 1][2];
int dph[MAX_N + 1][2];

int ASL()
{
	dp[1][0] = e1 + S1[1]; /* LINE 1 */
	dp[1][1] = e2 + S2[1]; /* LINE 2 */

	for (int i = 2; i <= N; ++i)
	{
		/* LINE 1 */
		dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + T2[i - 1]) + S1[i];

		/* LINE 2 */
		dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + T1[i - 1]) + S2[i];
	}

#ifdef DEBUG
	printf(" S ");
	for (int i = 1; i <= N; ++i) {
		printf("%5d", i);
	}
	printf("\n");
	printf(" 1 ");
	for (int i = 1; i <= N; ++i) {
		printf("%5d", dp[i][0]);
	}
	printf("\n");
	printf(" 2 ");
	for (int i = 1; i <= N; ++i) {
		printf("%5d", dp[i][1]);
	}
	printf("\n");
#endif

	return min(dp[N][0] + x1, dp[N][1] + x2);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\asl.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d %d %d %d", &N, &e1, &e2, &x1, &x2);
	/* N */
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &S1[i]);
	}
	/* N */
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &S2[i]);
	}
	/* N - 1 */
	for (int i = 1; i < N; ++i) {
		scanf("%d", &T1[i]);
	}
	/* N - 1 */
	for (int i = 1; i < N; ++i) {
		scanf("%d", &T2[i]);
	}

	int result = ASL();
	printf("%d\n", result);
	return 0;
}

#if 0

D[i][j] = 현재 물건이 i번 생산라인에서 왔을 때 ...

#endif
