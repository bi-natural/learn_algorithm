/*
 * DP: 폐지 줍기 
 *
 --
<문제>
N×N 격자로 이루어진 도시가 있다. 이 도시 군데군데에는 폐지가 버려져 있다.

범수는 가장 왼쪽 위 격자 (1, 1)에서 출발하여 가장 오른쪽 아래 격자 (N, N)까지 이동하며 폐지를 줍는데, 
최단 경로를 따라가야만 한다. 즉, 인접한 오른쪽 칸 또는 아래쪽 칸으로만 이동할 수 있다. 이 때, 
범수가 수집할 수 있는 폐지의 최대값을 출력하시오.

출발점과 도착점에 위치한 폐지 또한 주울 수 있다.

 --
 
A[x][y] : (x,y)에 있는 폐지의 양

위에서 왔을때 옆에서 왔을때의 폐지양 + 지금폐지양 으로 계속 업데이트.
 
D[x][y] = max (D[x-1][y] + A[x][y], D[x][y-1] + A[x][y])


 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

#define DEBUG 

const int MAX_N = 200;
const int MAX_G = 1000;

int N;
int A[MAX_N + 9][MAX_N + 9];

int dp[MAX_N + 9][MAX_N + 9];
int dph[MAX_N + 9][MAX_N + 9];

int PAPER(int sx, int sy)
{
	int& ref = dp[sx][sy];

	if (ref != -1)
		return ref;

	if (sx == N && sy == N)
		return ref = A[sx][sy];

	ref = 0;
	if (sx >= 1 && sx < N)
		ref = max(ref, A[sx][sy] + PAPER(sx + 1, sy));
	if (sy >= 1 && sy < N)
		ref = max(ref, A[sx][sy] + PAPER(sx, sy + 1));

	return ref;
}
 
int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\paper.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			(void) scanf("%d", &A[i][j]);
		}

	memset(dp, -1, sizeof(dp));
	int result = PAPER(1, 1);

#ifdef DEBUG
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			printf("%3d", dp[i][j]);
		}
		printf("\n");
	}
#endif

	printf("%d\n", dp[1][1]);

}
