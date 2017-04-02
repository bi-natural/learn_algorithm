/*
 * 정사각형 
 *
 --
 1로만 이루어진 정사각형을 1-정사각형이라고 한다.
 0과 1로 이루어진 N*N 사각형이 주어질 때, 크기 2*2 이상의 1-정사각형을 찾아 개수를 출력하자.
 --
 MAX_N = 257 
 O (N^3)
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N           257

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 
int A[2][MAX_N][MAX_N];
int* current_p[MAX_N][MAX_N], next_p[MAX_N][MAX_N];

int D[MAX_N][MAX_N];

int SQUARE2()
{
	for (int i = 1; i <= N; ++i) {
		D[i][1] = A[0][i][1];
		D[1][i] = A[0][1][i];
	}
		
	for (int i = 2; i <= N; ++i)	
		for (int j = 2; j <= N; ++j) {
			if (A[0][i][j] == 0) 
				D[i][j] = 0;
			else {
				int m1 = min(D[i-1][j], D[i-1][j-1]);
				int m2 = min(m1, D[i][j-1]);
				
				D[i][j] = min(m1, m2) + 1;
			}
		}	
		
	int result = 0;
		
#ifdef DEBUG
	printf("D = \n");
	for (int i = 1; i <= N; ++i, printf("\n"))	for (int j = 1; j <= N; ++j) {
		printf("%5d", D[i][j]);
		result += (D[i][j] > 1) ? D[i][j] - 1: 0;
	}
#endif
	return result;
}

int SQUARE1()
{
	int count = 0;
	int round = 0;
	
	memset(A[1], 0, sizeof(A[1]));
	
	for (int iter = 1; iter <= N; ++iter) {
		int count_saved = count;
		
		for (int i = 1; i < N; ++i)	for (int j = 1; j < N; ++j) {
			if (A[round][i][j] && A[round][i+1][j] && A[round][i][j+1] && A[round][i+1][j+1]) {
				A[1-round][i][j] = 1;
				count++;				
			}
			else {
				A[1-round][i][j] = 0;
			}
		}		

		if (count_saved == count) {
#ifdef DEBUG
			printf("!! no more reduced...\n");
#endif			
			return count;
		}

#ifdef DEBUG
		printf("iteration %d\n", iter);
		for (int i = 1; i < N; ++i, printf("\n"))	for (int j = 1; j < N; ++j) {
			printf("%5d", A[1-round][i][j]);
		}	
#endif
		/* round chanage */
		round = 1 - round;
	}
	
	return count;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\square1.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			scanf("%d", &A[0][i][j]);
		
#ifdef DEBUG
	printf("A = \n");
	for (int i = 1; i < N; ++i, printf("\n"))	for (int j = 1; j < N; ++j) {
		printf("%5d", A[0][i][j]);
	}	
#endif
	int result = SQUARE1();
	
	printf("%d\n", result);
	return 0;
}

