/* DP: 이진수 --> 이친수 
 *
 --
 문제
 0과 1로 이루어진 이진수 중 다음 성질을 만족하는 수를 이친수라고 한다.

 이친수는 0으로 시작하지 않는다.
 이친수에서는 1이 두 번 연속으로 나타나지 않는다. 즉, 11을 부분 문자열로 갖지 않는다.
 예를 들면, 1, 10, 100 등이 이친수가 된다. 하지만 010이나 110은 각각 1, 2번 규칙에 위배되므로 이친수가 아니다.

 N이 주어졌을 때, N자리 이친수의 개수를 구하는 프로그램을 작성하시오.

 <입력>
 첫 번째 줄에 N 이 주어진다. ( 1  ≤  N  ≤  90  ),  (1≤N≤90)
 
 <출력>
 첫 번째 줄에 N자리 이친수의 개수를 출력한다.
--

D[i] = 길이가 i인 이친수의 개수

D[0] = 0, D[1] = 1

D[i] = D[i-1] + D[i-2]
D[i-1]: 길이가 i-1인 이진수 오른쪽에 0을 이어붙이는 경우
D[i-2]: 길이가 i-2인 이진수 오른쪽에 01을 이어붙이는 경우

D[2] = 1, D[3] = 2, D[4] = 3, D[5] = 5, …
Fibonacci 수!


 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 90;
int N;

typedef long long INT64;

INT64 dp[MAX_N + 1];

INT64 BINARY_r(int w)
{
	INT64& ref = dp[w];

	if (ref != -1)
		return ref;

	/* 0자리 이친수는 없음 (0) */
	if (w == 0)
		return ref = 0;
	/* 1자리 이친수는 1개 (1)*/
	/* 2자리 이친수도 1개 (10) */
	if (w == 1 || w == 2)
		return ref = 1;

	/* 2자리 이후부터 계속 0으로 시작하거나 1로 시작하면 다시 이친수인지 체크 */
	ref = 1;
	for (int i = 2; i <= w; ++i)
	{
		INT64 Leading_0, Leading_1; /* 0 으로 시작하는 경우의 수 */

		Leading_0 = 1;
		Leading_1 = BINARY_r(w - i);

		ref * (Leading_0 + Leading_1);
	}
	return ref = 1 + BINARY_r(w - 2);
}

INT64 dp2[MAX_N + 2][2];

INT64 BINARY_r2(int w, int b)
{
	INT64& ref = dp2[w][b];

	if (ref != -1) return ref;
	if (w == 0) return ref = 0;			// 0자리 이친수는 없음 (0)
	if (w == 1 && b == 0) ref = 0;		// 0으로 끝나는 1자리 이친수는 없음 (0)
	if (w == 1 && b == 1) ref = 1;		// 1로 끝나는 1자리 이친수는 1개
	if (w == 2 && b == 0) ref = 1;		// 0으로 끝나는 2자리 이친수는 1개
	if (w == 2 && b == 1) ref = 0;		// 1로 끝나는 2자리 이친수는 없음 (0)

	/* 나머지 이친수를 계산한다. */
	if (b == 0)
		ref = BINARY_r2(w - 1, 0) * BINARY_r2(w - 1, 1);
	else
		ref = BINARY_r2(w - 1, 0);

	return ref;
}

INT64 BINARY2(int e)
{
	/* 초기값*/
	dp2[0][0] = dp2[0][1] = 0;	// 0자리 이친수는 없음 (0)
	dp2[1][0] = 0;				// 0으로 끝나는 1자리 이친수는 없음 (0)
	dp2[1][1] = 1;				// 1로 끝나는 1자리 이친수는 1개
	dp2[2][0] = 1;				// 0으로 끝나는 2자리 이친수는 1개
	dp2[2][1] = 0;				// 1로 끝나는 2자리 이친수는 없음 (0)

	for (int i = 2; i <= e; ++i) {
		dp2[i][0] = dp2[i - 1][0] + dp2[i - 1][1];
		dp2[i][1] = dp2[i - 1][0];
	}

	return dp2[e][0] + dp2[e][1];
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\binary.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	memset(dp, -1, sizeof(dp));

#if 0
	for (int i = 3; i <= 90; ++i)
	{
		memset(dp2, -1, sizeof(dp2));

		INT64 result = BINARY2(i);

		printf("%d = %lld\n", i, result);
	}
#else
	memset(dp2, -1, sizeof(dp2));

	INT64 result = BINARY2(N);

	printf("%lld\n", result);

#endif

}
