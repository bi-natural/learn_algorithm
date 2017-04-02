/*
 * 내리막길 
 --
 지도가 주어질 때 이와 같이 제일 왼쪽 위 지점에서 출발하여 제일 오른쪽 아래 
 지점까지 항상 내리막길로만 이동하는 경로의 개수를 구하는 프로그램을 작성하시오.

 경우의 수가 많기 때문에 전체 경우를 1234567로 나눈 가짓수를 출력한다.

<입력> 
첫째 줄에는 지도의 세로의 크기 M과 가로의 크기 N이 빈칸을 사이에 두고 주어진다. 
이어 다음 M개 줄에 걸쳐 한 줄에 N개씩 위에서부터 차례로 각 지점의 높이가 빈 칸을 
사이에 두고 주어진다. M과 N은 각각 500이하의 자연수이고, 각 지점의 높이는 
1,000,000이하의 자연수이다
 --
 
 입력이 크지만 조건에 제약사항이 있어 항상 같은 포지션에서는 같은 액션만 취할수
 있어 메모이제이션을 이용하면 시간내 풀림. 
 DFS를 사용하여 탐색. 
 
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N 507

using namespace std;

typedef long long INT64;
typedef pair<int, int> INTPAIR;

int CASE; 
int H, W;
int A[MAX_N][MAX_N];
int D[MAX_N][MAX_N];

int df[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };

int X[4]= { 1, -1, 0, 0 };
int Y[4] = { 0, 0, 1, -1 };

int dfs(int sy, int sx)
{
	if (sy == H && sx == W)
		return 1;
		
	int& possible = D[sy][sx];

	if (possible != -1)
		return possible;
	
	possible = 0;
		
	int here = A[sy][sx];	
	for (int i = 0; i < 4; ++i) {
		int dy = sy + df[i][0];
		int dx = sx + df[i][1];
		
		if (dy >= 1 && dy <= H && dx >= 1 && dx <= W) {
			int there = A[dy][dx];
			
			if (there < here) {
				possible = ( possible + dfs(dy, dx) ) % 1234567;
			}
		}
	}
	return possible % 1234567;
}

int DOWN(int sx, int sy)
{
	memset(D, -1, sizeof(D));
	
	return dfs(sx, sy);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\down.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d %d", &H, &W);
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			scanf("%d", &A[i][j]);
	
#ifdef DEBUG
	printf("%d %d\n", H, W);
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j)
			printf("%3d", A[i][j]);
		printf("\n");		
	}
#endif
	int result = DOWN(1,1);
	
	printf("%d\n", result);
	return 0;
}

