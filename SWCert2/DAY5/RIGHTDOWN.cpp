/* 출근: */

/*
 
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

#define DEBUG 

typedef long long INT64;
typedef pair<int, int> intpair;

const int MAX_H = 1000;
int H, W, N;
int A[MAX_H + 9][MAX_H + 9];
int B[MAX_H + 9][MAX_H + 9];

pair<int, int> SOLVE(int n)
{
	/* 바로 전날의 상태를 구한다. */
	int target = n - 1;

#ifdef DEBUG
	printf("A = \n");
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			printf("%3d", A[i][j]);
		}
		printf("\n");
	}
#endif

	memset(B, 0, sizeof(B));
	B[1][1] = target;
	
	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j) {
			if (A[i][j] == 1)
			{
				/* 최초가 (오른쪽)이였다면 */
				B[i][j + 1] += B[i][j] / 2 + B[i][j] % 2;
				B[i + 1][j] += B[i][j] / 2;
			}
			else {
				/* 최초가 아래쪽이였다면 */
				B[i + 1][j] += B[i][j] / 2 + B[i][j] % 2;
				B[i][j + 1] += B[i][j] / 2;
			}
		}

#ifdef DEBUG
	printf("B = \n");
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			printf("%3d", B[i][j]);
		}
		printf("\n");
	}
#endif

	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			B[i][j] = (B[i][j] % 2) ? 1 - A[i][j] : A[i][j];

#ifdef DEBUG
	printf("B = \n");
	for (int i = 1; i <= H; ++i) {
		for (int j = 1; j <= W; ++j) {
			printf("%3d", B[i][j]);
		}
		printf("\n");
	}
#endif

	int i = 1, j = 1;

	while (i <= H && j <= W) {
		if (B[i][j])
			j++;
		else
			i++;
	}

	return pair<int, int>(i, j);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\rightdown.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif

	scanf("%d %d %d", &H, &W, &N);

	for (int i = 1; i <= H; ++i)
		for (int j = 1; j <= W; ++j)
			scanf("%d", &A[i][j]);

	pair<int, int>result = SOLVE(N);

	printf("%d %d\n", result.first, result.second);
}