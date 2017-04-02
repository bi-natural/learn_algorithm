/* DP: Adjacent Bit */

/**
문제
0과 1로 이루어진 수열 S가 주어진다. S의 첫 수를 s_1, 마지막 수를 s_N이라고 할 때, S의 인접한 비트의 개수는 다음과 같이 구할 수 있다.

s_1 x s_2 + s_2 x s_3 + s_3 x s4 + ... + s(N-1) x s_N

위의 식을 이용하면 수열 S에서 인접한 1의 개수를 구할 수 있다. 예를들어, 011101101의 인접한 비트의 개수는 3이 되고, 111101101은 4, 010101010은 0이 된다.

수열 S의 크기 N과 K가 주어졌을 때, 인접한 비트의 개수가 k인 수열 S의 개수를 구하는 프로그램을 작성하시오.

예를 들어, N이 5이고, K가 2이면, 수열 S가 될 수 있는 수열은 다음과 같이 6가지가 있다.

11100
01110
00111
10111
11101
11011


<입력>
첫 번째 줄에 테스트 케이스의 수 T가 주어진다. (1 ≤ T ≤ 1,000)

각 테스트 케이스의 첫 번째 줄에 세 정수 t, N, K가 공백으로 분리되어 주어진다. t는 테스트 케이스의 번호이다. (1 ≤ N ≤ 100)

출력
각 테스트 케이스에 대해 테스트 케이스 번호와 인접한 비트의 개수가 k인 수열 S의 개수를 사이에 공백을 두고 한 줄에 하나씩 출력한다.

이 값은 2,147,483,647보다 작거나 같다.

<풀이>

길이가 N인 이진수열 중에 N번째 수가 x이면서 (x = 0 or 1) 인접한 비트의 갯수가 K인 경우의 수 
D[N][K][x]

D[N][K][0] = D[N-1][K][0] + D[N-1][K][1]
D[N][K][1] = D[N-1][K][0] + D[N-1][K-1][1]
 
정답 = D[N][K][0] + D[N][K][1]

*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;

const int MAX_N = 100;
const INT64 MAX_MOD = 2147483647;
int CASE, T, N, K;
INT64 A[MAX_N + 9];

INT64 dp[MAX_N + 2][MAX_N + 1][3];

INT64 ADJ_BIT_r(int n, int k, int b)
{
	INT64& ref = dp[n][k][b];

	if (ref != -1)
		return ref;

	/* DP[0][x][x] = 0 */
	if (n == 1)
	{
		if (k == 0)
			return ref = 1;
		else
			return ref = 0;
	}

	/* 0 으로 끝나는 경우의 수 */
	if (b == 0) {
		ref = ADJ_BIT_r(n - 1, k, 0) + ADJ_BIT_r(n - 1, k, 1);
	}
	else
	{
		/* 1 로 끝나는 경우 */
		ref = ADJ_BIT_r(n - 1, k, 0) + ADJ_BIT_r(n - 1, k - 1, 1);
	}

	return ref %= 2147483647;
}

int main()
{

#ifdef DEBUG
	freopen("C:\\temp\\adj_bit.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d", &CASE);

	memset(dp, -1ll, sizeof(dp));

	for (int t = 1; t <= CASE; ++t) {
		scanf("%d %d %d", &T, &N, &K);

		INT64 result = ADJ_BIT_r(N+1, K, 0);
		
#ifdef DEBUG
		if (N == 5)
		{
			for (int i = 0; i < N + 1; ++i)
				for (int j = 0; j < K; ++j) {
					printf("%10d", dp[i][j][0]);
				}
			printf("\n");
		}
#endif
		printf("%d %lld\n", T, result);
	}
}
