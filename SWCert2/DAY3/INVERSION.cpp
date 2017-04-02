/* 
 * 탐색/정렬: Inversion 개수 
 *
 --
 --
 
 MergeSort를 사용한 Inversion Count 개수 구하기. 
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>

#define DEBUG

using namespace std;

typedef long long INT64;

const int MAX_N = 100000;

int N;

int A[MAX_N + 9];
int tmp[MAX_N + 9];

/* Use : Merge Sort */
INT64 MergeComplete(int Ls, int Le, int Rs, int Re)
{
	INT64 count = 0ll;
	int l_pos = Ls, r_pos = Rs;
	int t_pos = Ls;

	while (l_pos != Le || r_pos != Re)
	{
		if (l_pos == Le) {
			tmp[t_pos++] = A[r_pos++];
			continue;
		}

		if (r_pos == Re) {
			tmp[t_pos++] = A[l_pos++];
			continue;
		}

		if (A[l_pos] <= A[r_pos]) {
			tmp[t_pos++] = A[l_pos++];
		}
		else {
			/* Inversion을 확인하는 경우 */
			tmp[t_pos++] = A[r_pos++];
			count += (Le - l_pos);
		}
	}

	for (int i = Ls; i < Re; ++i)
		A[i] = tmp[i];

#ifdef DEBUG
	printf("MergeComplete(%3d,%3d - %3d,%3d): ", Ls, Le, Rs, Re);
	for (int i = Ls; i < Re; ++i) printf("%3d", A[i]);
	printf("\n");
#endif
	return count;

}

INT64 MergeSort(int s, int e)
{
	INT64 count = 0;

#ifdef DEBUG
	printf("MergeSort(%3d,%3d) -- enter\n", s, e);
#endif

	/* 기저존건 */
	if (s >= e)
		return 0ll;

	if ((s + 1) == e) {
#ifdef DEBUG
		printf("MergeSort(%3d,%3d) -- leave\n", s, e);
#endif

		if (A[s] > A[e]) {			/* inversion 1개 증가 */
			swap(A[s], A[e]);
			return 1ll;
		}
		return 0ll;
	}

	/* 분할 */
	int mid = (s + e) / 2;

	count += MergeSort(s, mid);
	count += MergeSort(mid + 1, e);

	count += MergeComplete(s, mid + 1, mid + 1, e + 1);
#ifdef DEBUG
	printf("MergeSort(%3d,%3d) -- leave\n", s, e);
#endif
	return count;
}

INT64 INVERSION()
{
	INT64 result = MergeSort(1, N);

#ifdef DEBUG
	for (int i = 1; i <= N; ++i)
		printf("%5d", A[i]);
	printf("\n");
#endif
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\inversion.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i) {
		scanf("%d", A + i);
	}

	INT64 result = INVERSION();

	printf("%lld\n", result);
	return 0;
}
