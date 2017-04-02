/*
 * 세금 
 *
 ---
 납세의 의무는 국민의 기본적인 의무이다. 세금은 수입에 비례하여 정해진 규칙에 따라 계산되기 때문에,
 규칙에 따라서 정확한 수입을 계산하는 것이 중요하다. 
 여러분은 새로 가게를 열고, 총 N 일 동안 영업을 하였다. 
 납세의 의무를 성실하게 수행하기 위하여 매 영업일마다 손익(이익 또는 손해)을 기록하여 세무서에 
 신고하였다. 세금을 매기는데 기준이 되는 수입은 다음 규칙에 의해서 계산된다.

"1일부터 N일 사이의 어떤 연속된 기간에 대하여 이 기간 동안 손익의 총합을 구한다. 
단, 하루 이상의 기간만 고려한다. 다음, 전체 가능한 모든 기간에 대하여 구한 손익의 총합들 중 
K번째로 큰 값이 기준이 된다. 즉, 총합들을 내림차순으로 정렬했을 때 K번째 값이다."

예를 들어, 총 3일간 영업을 하였다면 1일, 1일~2일, 1일~3일, 2일, 2일~3일, 3일 총 6가지 
기간에 대하여 각 기간마다 손익의 총합을 구하고, 이 중 K번째 큰 값이 세금의 기준이 된다.
 ---
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG
#define MAX_N           1000007
#define MAX_K                57
#define MIN_COST 	-1000000007

using namespace std;

typedef long long INT64;
typedef pair<int, int> PPI;

int CASE; 
int N, K; 
INT64 A[MAX_N];
INT64 LocalTopK[MAX_K];
INT64 GlobalTopK[2][MAX_K];
INT64 *global_top, *global_tmp;

/*
 * LocalTopK[i][20]   : 이전 iteration까지 돌았을때 i번째 숫자를 포함한 부분합 수열들중에 
                        내림차순 정렬했을 때 1~k번째 순서값의 정렬 
                        --> 여기서 [i]는 너무 크기 때문에 생략 
                        
 * GlobalTopK[i]      : 모든 LocalTopK 들에 대해서 역대 최대값들의 정렬 
 */
 
template <typename T>
int BSEARCH(T arr[], int arrsize, T x)
{
	int low = 0, high = arrsize - 1;
	
	while (low <= high)	 {
		int mid = (low + high) >> 1;
		
		if (arr[mid] < x)
			low = mid + 1;
		else if (arr[mid] > x)
			high = mid - 1;
		else
			return mid;
	}
	
	return high;
}

template <typename T>
int BSEARCH_r(T arr[], int arrsize, T x)
{
	int low = arrsize-1, high = 0;
	
	while (low <= high)	 {
		int mid = (low + high) >> 1;
		
		if (arr[mid] < x)
			low = mid + 1;
		else if (arr[mid] > x)
			high = mid - 1;
		else
			return mid;
	}
	
	return low;
}

INT64 TAX()
{
	/* 초기화: K번째 까지는 모두 최소값으로 채우기 */ 
	for (int i = 1; i <= K; ++i) {
		LocalTopK[i] = MIN_COST;
		GlobalTopK[0][i] = MIN_COST;
	}
		
	global_top = GlobalTopK[0];
	global_tmp = GlobalTopK[1];
	
#ifdef DEBUG
		printf("inital iteration(%d) local = ", 0);
		for (int j = 1; j <= K; ++j) {
			if (LocalTopK[j] != MIN_COST)
				printf("%5d", LocalTopK[j]);
		}
		printf("\n");
#endif	
#ifdef DEBUG
		printf("initial iteration(%d) global = ", 0);
		for (int j = 1; j <= K; ++j) {
			if (global_top[j] != MIN_COST)
				printf("%5d", global_top[j]);
		}
		printf("\n");
#endif

	for (int i = 1; i <= N; ++i) {
		/* i로 끝나는 것에 대해서 LocalTopK 계산  */	
		for (int j = 1; j <= K; ++j) if (LocalTopK[j] != MIN_COST)
			LocalTopK[j] += A[i];
		
		/* A[i]와 비교하여 위치시켜 줌 (K번째 이전이므로 그냥 for loop) --> 크면 Binary Search */

		int found = 1;
		for ( ; found <= K; ++found) if (LocalTopK[found] < A[i])
			break;

		int found2 = BSEARCH_r(LocalTopK + 1, K, A[i]);
		
#ifdef DEBUG
		printf("%d == BSERACH_r(LocalTopK, %lld) = %d\n", found, A[i], found2);
#endif
		if (found <= K)
		{
			LocalTopK[K] = A[i]; /* 맨마지막 대신에 A[i]로 교체 */ 
			
			/* lb 위치까지 계속 교체 */ 
			for (int up = K; up != found; --up) {
				swap(LocalTopK[up], LocalTopK[up-1]);
			}
		}

#ifdef DEBUG
		printf("iteration(%d) local = ", i);
		for (int j = 1; j <= K; ++j) {
			if (LocalTopK[j] != MIN_COST)
				printf("%5d", LocalTopK[j]);
		}
		printf("\n");
#endif
	
		/* LocalTopK에서 GlobalTopK 보다 높은 것들이 있으면 GlobalTopK에 반영해 줌 */
		/*
		 * Merge GlobalTopK + LocalTopK --> next GlobalTopK 
		 */
		int j = 1, k = 1, n = 1;
		
		while (n <= K && (j <= K || k <= K))  {
			if (j == K+1 || global_top[j] < LocalTopK[k])
				global_tmp[n++] = LocalTopK[k++];
			else if (k == K+1 || global_top[j] >= LocalTopK[k])
				global_tmp[n++] = global_top[j++];
		}
		
		swap(global_tmp, global_top);
#ifdef DEBUG
		printf("iteration(%d) global = ", i);
		for (int j = 1; j <= K; ++j) {
			if (global_top[j] != MIN_COST)
				printf("%5d", global_top[j]);
		}
		printf("\n");
#endif
	}

	return global_top[K];
}

int main()
{
#ifdef DEBUG
	freopen("input\\tax.txt", "r", stdin);
	freopen("output\\result.txt", "w", stdout);
#endif	

	scanf("%d %d", &N, &K);
	
	for (int i = 1; i <= N; ++i)
		scanf("%lld", A+i);
		
	INT64 result = TAX();
	
	printf("%lld\n", result);
	return 0;
}

