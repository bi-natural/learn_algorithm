/*
 * 정사각형 
 *
 --
 1로만 이루어진 정사각형을 1-정사각형이라고 한다.
 0과 1로 이루어진 N*N 사각형이 주어질 때, 크기 2*2 이상의 1-정사각형을 찾아 개수를 출력하자.
 
 MAX_N = 3000 
 O (N^2)
 --
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N           3007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 
int A[MAX_N][MAX_N];
INT64 D[MAX_N][MAX_N];

/*
 * D[i][j] --> 0 .. k 
 * 
 * 정의: (i, j) 좌표를 끝점으로 하는 정사각형에 대해 모두 1로 채워진 개수 
 *     D[i][j] = 0 : A[i][j]조차도 1이 아니다. 
 *     D[i][j] = 1 : A[i][j]만 1이다.
 *     D[i][j] = 2 : A[i-1][j-1]좌표부터 A[i][j]까지 모두 1이다. (k는 정사각형의 크기) 
 *     D[i][j] = k : A[i-k+1][j-k+1]좌표부터 A[i][j]까지 모두 1이다. (k는 정사각형의 크기) 
 */

INT64 min3(INT64 a, INT64 b, INT64 c) 
{
	return min(a, min(b, c));
}

INT64 SQUARE2()
{
	/* 초기화 : 맨 위쪽과 맨 좌측에 값을 세팅. D[i][j]의 k값은 1의 개수  */ 
	for (int i = 1; i <= N; ++i) {
		D[i][1] = (INT64) A[i][1];
		D[1][i] = (INT64) A[1][i];
	}

	/* 2..N까지 D[i][j]를 구한다. */
	INT64 result = 0ll;
	
	for (int i = 2; i <= N; ++i)	
		for (int j = 2; j <= N; ++j) {
			if (A[i][j] == 0) 
				D[i][j] = 0ll;
			else {
				D[i][j] = min3(D[i-1][j], D[i-1][j-1], D[i][j-1]) + 1ll;
				if (D[i][j] > 1ll)
					result += (D[i][j] - 1ll);
			}
		}	
		
#ifdef DEBUG
	printf("D = \n");
	for (int i = 1; i <= N; ++i, printf("\n"))	for (int j = 1; j <= N; ++j) {
		printf("%5lld", D[i][j]);
	}
#endif
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("input\\square1.txt", "r", stdin);
	freopen("output\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			scanf("%d", &A[i][j]);
		
#ifdef DEBUG
	printf("A = \n");
	for (int i = 1; i < N; ++i, printf("\n"))	for (int j = 1; j < N; ++j) {
		printf("%5d", A[i][j]);
	}	
#endif
	INT64 result = SQUARE2();
	
	printf("%lld\n", result);
	return 0;
}

