/* DP: 최대 부분함 */

/**
문제
크기
N
N인 정수 배열이 들어왔을 때 연속 부분 수열 중 합이 최대인 것의 합을 구하시오.

<입력>
첫 번째 줄에 크기N이 주어진다.(1≤N≤1,000,000)
두 번째 줄에 크기N인 정수 배열이 주어진다. 주어지는 수의 절대값은 2,000,000 보다 크지 않다.

<출력>
연속 부분 수열의 합 중 최대값을 출력하시오. (단, 출력값이 int 범위를 벗어날 수 있다.)

<풀이>

 D[e] :e 로 끝나는 연속 부분수열중에 최대 합 

 D[e]중에 최대값이 답 
 
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;

const int MAX_N = 1000000;
const int MAX_V = 2000000;
int N;
INT64 A[MAX_N + 9];

/* D[e] :e 로 끝나는 연속 부분수열중에 최대 합 */

INT64 dp[MAX_N + 1];

INT64 MAXSUM_r(int e)
{
	INT64& ref = dp[e];

	if (ref != -1)
		return ref;

	/* 기저값 */
	if (e == 0)
	{
		return ref = 0ll;		/* 공집합 */
	}
		
	/* DP[n] = MAX { DP[n-1] + A[i], A[i] } */	

	ref = max(MAXSUM_r(e - 1) + A[e], A[e]);

	return ref;
}

int main()
{

#ifdef DEBUG
	freopen("C:\\temp\\maxsum.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%lld", A + i);
	}

	memset(dp, -1, sizeof(dp));

	INT64 result = MAXSUM_r(N);


	INT64 max_result = result;

	for (int i = 1; i <= N; ++i)
		max_result = max(dp[i], max_result);

	printf("%lld\n", max_result);
	return 0;
}
