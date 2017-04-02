/* 
 * 탐색: N-Queen 
 *
 --
N-Queen문제는 유명한 문제이다. 이는 N × N인 체스판 위에 N개의 퀸을 서로 공격할 수 없게 놓는 문제이다.

N이 주어졌을 때, 퀸을 놓는 방법의 수를 구하시오.
 --
 
<풀이>
백트랙킹: 특정순서대로 탐색하면서 가지치기로 경우의 수를 줄여 시간내 탐색

- 대부분 DFS를 이용한 재귀호출로 동작함.
- 가지치기를 위해 계산식을 간단하게 check하는 룰을 만들어야 한다. 

N-Queen : 대각선 및 가로/세로에 1개라도 check가 되면 특정 (i, j)위치의 check를 
O(1)에 할수 있음. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
const int MAX_Q = 12;
int N;

int answer = 0;

int col[MAX_Q + 9];
int d1[2 * MAX_Q + 9];
int d2[2 * MAX_Q + 9];

int dfs(int i)
{
	int answer = 0;

	if (i == N)
	{
		return 1;
	}

	for (int j = 0; j < N; ++j) 
	{
		if (col[j] || d1[i + j] || d2[i - j + N - 1])
			continue;

		col[j] = d1[i + j] = d2[i - j + N - 1] = 1;
		answer += dfs(i + 1);
		col[j] = d1[i + j] = d2[i - j + N - 1] = 0;
	}

	return answer;
}

int NQUEEN(int n)
{
	return dfs(0);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\nqueen.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	int result = NQUEEN(1);
	printf("%lld\n", result);
}
