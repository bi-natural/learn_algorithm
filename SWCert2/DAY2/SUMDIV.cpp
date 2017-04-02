/* DP: 합분해 */

/** 
문제
0부터 N 까지의 정수 K 개를 더해서 그 합이 N 이 되는 경우의 수를 구하는 프로그램을 작성하시오.

덧셈의 순서가 바뀐 경우는 다른 경우로 센다(1+2와 2+1은 서로 다른 경우). 또한 한 개의 수를 여러 번 쓸 수도 있다.

<입력>
첫 번째 줄에 두 정수N,K가 공백으로 분리되어 주어진다.
(1 ≤ N , K ≤ 200 )(1≤N,K≤200)

<출력>
첫 번째 줄에 답을1000000000으로 나눈 나머지를 출력한다.

<풀이> 
D[i][j] = i개의 수를 더해서 j를 만드는 경우의 수

초기값 D[0][0] = 1

D[i][j] = Sum of D[i-1][j-k] for all 0 ≤ k ≤ j
D[i-1][j-k]: 마지막에 더한 수가 k인 경우의 수

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;

const int MAX_N = 200;
const INT64 MOD_VALUE = 1000000000;

int N, K;

INT64 dp[MAX_N + 1][MAX_N + 1];

INT64 SUMDIV_r(int n, int k)
{
	INT64& ref = dp[n][k];

	if (ref != -1)
		return ref;

	if (n == 0)
		return ref = 1ll;

	if (k == 0)
		return ref = 0ll;

	ref = 0ll;
	for (int j = 0; j <= n; ++j)
	{
		ref += SUMDIV_r(n - j, k - 1);
		ref %= MOD_VALUE;
//		printf("SUMDIV_r(%d, %d)_ref = %lld\n", n - j, k - 1, SUMDIV_r(n - j, k - 1));
	}
	return ref;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\sumdiv.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d %d", &N, &K);

	memset(dp, -1, sizeof(dp));

	INT64 result = SUMDIV_r(N, K);

	printf("%lld\n", result);
	return 0;
}
