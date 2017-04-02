/*
 * 나누기 
 *
 --
 입력으로 주어진 종이의 한 변의 길이 N과 각 정사각형칸의 색(0 또는 1)이 주어질 때 잘린 조각들 중 
 0으로 칠해진 색종이의 수와 1로 칠해진 색종이의 개수를 구하는 프로그램을 작성하시오.
 
 <입력>
 첫째 줄에는 전체 종이의 한 변의 길이 N이 주어져 있다. 
 N은 2,4,8,16,32,64,128 중 하나이다. 색종이의 각 가로줄의 정사각형칸들의 색이 윗줄부터 차례로 
 둘째 줄부터 마지막 줄까지 주어진다.

각 숫자 사이에는 빈칸이 하나씩 있다.  
 --
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;
typedef pair<int, int> INTPAIR;

#define MAX_N 509

int CASE; 
int N;
int A[MAX_N][MAX_N];

/*
 * 4개면으로 분할하여 만듬
 *
 * 전체 0의 개수와 1의 개수를 리턴하되 All Zero/All One에 대해서 
 * 대표로 한개만 리턴함. (이때, 없는 개수를 세는게 편함) 
 */
INTPAIR COUNT(int sx, int sy, int size)
{
	if (size == 1)	{
		return A[sx][sy] ? INTPAIR(0, 1) : INTPAIR(1, 0);
	}
	
	int halfN = size / 2;
	
#ifdef DEBUG
	printf(" -- COUNT (%d, %d, %d)\n", sx, sy, size);
	printf("    -- Q1 (%d, %d, %d)\n", sx, sy, halfN);
	printf("    -- Q2 (%d, %d, %d)\n", sx + halfN, sy, halfN);
	printf("    -- Q3 (%d, %d, %d)\n", sx, sy + halfN, halfN);
	printf("    -- Q4 (%d, %d, %d)\n", sx + halfN, sy + halfN, halfN);
#endif
	
	INTPAIR q1 = COUNT(sx, sy, halfN);
	INTPAIR q2 = COUNT(sx + halfN, sy, halfN);
	INTPAIR q3 = COUNT(sx, sy + halfN, halfN);
	INTPAIR q4 = COUNT(sx + halfN, sy + halfN, halfN);
	
	int zeros = q1.first + q2.first + q3.first + q4.first;
	int ones = q1.second + q2.second + q3.second + q4.second;

#ifdef DEBUG
	printf(" !! COUNT (%d, %d, %d) --> (%d, %d) size^2 = %d\n", sx, sy, size, zeros, ones, size*size);
#endif	

	if (zeros == 0)
		return INTPAIR(0, 1);
	else if (ones == 0)
		return INTPAIR(1, 0);
	else
		return INTPAIR(zeros, ones);
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\divide.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif	

	scanf("%d", &N);
	
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) 
			scanf("%d", &A[i][j]);
			
	INTPAIR result = COUNT(1, 1, N);
	printf("%d\n%d\n", result.first, result.second);
	return 0;
}

