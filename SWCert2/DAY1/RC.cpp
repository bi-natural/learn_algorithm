/* 
 * 막대자르기(Rod Cutting)
 *
 --
 길이가 N인 막대기가 있다. 막대기를 길이가 자연수가 되도록 여러 조각으로 자를 수 있다. 
 각 길이에 대해 값어치가 있을 때, 값어치 합이 최대가 되도록 막대기를 자르자.

예를 들어, 길이가 4인 막대기가 있고 각 길이 별 값어치가 아래와 같다고 하자.

|  length  | 1 | 2 | 3 | 4 |
|----------|---|---|---|---|
|   cost   | 1 | 5 | 8 | 9 |
이 때, 길이 2인 막대기가 두 개가 되도록 전체 막대기를 자를 경우 전체 값어치가 10이 되어 최대가 된다.

<입력>
첫 줄에 막대기의 길이 N이 주어진다. (1≤N≤3,000)

둘째 줄에 N개의 자연수가 공백으로 구분되어 주어지는데, i번째로 주어지는 수는 길이가 
i인 막대기의 값어치를 의미한다. 이 때 주어지는 수는 1,000를 넘지 않는다. 
 --
 
<풀이>

C[i] = 길이가 i인 막대기 조각의 값어치
D[i] = 길이가 i인 막대기를 여러 조각으로 잘랐을 때, 전체 값어치의 최대값

	- D[0] = 0
	- D[i] = max(D[j] + C[i-j]) (for all 0 ≤ j ≤ i-1)
	         최근에 자른 막대기 조각의 길이가 i-j일 때
 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

// #define DEBUG

const int MAX_N = 3000;

int N; 
int A[MAX_N + 1];

int dp[MAX_N + 1];
int dph[MAX_N + 1];

int RC()
{
	dp[0] = 0;

	for (int n = 1; n <= N; ++n) {
		int q = -1;

		for (int cut = 1; cut <= n; ++cut) {
			int p = A[cut];
			int r = dp[n - cut];

			if (q < p + r) {
				q = p + r;
				dph[n] = cut;
			}
		}
		dp[n] = q;
	}
	return dp[N];
}

int RC_r(int n)
{
	int& ref = dp[n];

	if (ref != -1)
		return ref;

	if (n == 0)
		return ref = 0;

	ref = 0;
	int q = -1;
	for (int cut = 1; cut <= n; ++cut) {
		int p = A[cut];
		int r = RC_r(n - cut);

		if (q < p + r) {
			q = p + r;
			dph[n] = cut;
		}
	}

	return ref = q;
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		scanf("%d", &A[i]);
	}

	memset(dp, -1, sizeof(dp));
	memset(dph, -1, sizeof(dph));

	int result = RC_r(N);
	printf("%d\n", result);

#ifdef DEBUG
	printf("\nEnter any number:...");
	int ch;
	
	scanf("%d", &ch);
#endif
	return 0;
}

#if 0

A[i] = 길이가 i인막대기 조각의 값어치  (입력으로 주어짐)
 
D[i] = 길이가 i인막대기를 여러 조각으로 잘랐을 때, 전체 값어치의 최대값

D[0] = 0

D[i] = max(D[i-j] + A[j])   (for all 1<= j <= i)
	* 최근에 자른 막대기 조작의 길이가 j 일때

#endif
