/* 
 * 탐색: COWS 
 *
 --
 --
 Cyclic shift 사용
 
   * inversion count 를 구해 conflict 를 계산후
   * shift 해가면서 변화하는 inversion count 계산; 이떼 이전에 계산한 inversion count 사용
   *  
 */

#define _SCL_SECURE_NO_WARNINGS

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
int B[MAX_N + 9];
int AMAP[MAX_N + 9];
int tmp[MAX_N + 9];
INT64 CROSS[MAX_N + 9];

/* Use : Merge Sort */
INT64 MergeComplete(int B[], int arrsize, int Ls, int Le, int Rs, int Re)
{
	INT64 count = 0ll;
	int l_pos = Ls, r_pos = Rs;
	int t_pos = Ls;

	while (l_pos != Le || r_pos != Re)
	{
		if (l_pos == Le) {
			tmp[t_pos++] = B[r_pos++];
			continue;
		}

		if (r_pos == Re) {
			tmp[t_pos++] = B[l_pos++];
			continue;
		}

		if (B[l_pos] <= B[r_pos]) {
			tmp[t_pos++] = B[l_pos++];
		}
		else {
			/* Inversion을 확인하는 경우 */
			tmp[t_pos++] = B[r_pos++];
			count += (Le - l_pos);
		}
	}

	for (int i = Ls; i < Re; ++i)
		B[i] = tmp[i];

	return count;

}

INT64 MergeSort(int B[], int arrsize, int s, int e)
{
	INT64 count = 0;

	/* 기저존건 */
	if (s >= e)
		return 0ll;

	if ((e - s) == 1) {
		if (B[s] > B[e]) {			/* inversion 1개 증가 */
			swap(B[s], B[e]);
			return 1ll;
		}
		return 0ll;
	}

	/* 분할 */
	int mid = (s + e) / 2;

	count += MergeSort(B, arrsize, s, mid);
	count += MergeSort(B, arrsize, mid + 1, e);

	count += MergeComplete(B, arrsize, s, mid + 1, mid + 1, e + 1);
	return count;
}

INT64 INVERSION(int B[], int arrsize)
{
#ifdef DEBUG
	for (int i = 1; i <= N; ++i) {
		printf("%3d", B[i]);
	}
	printf("\n");
#endif

	INT64 result = MergeSort(B, arrsize, 1, N);

#ifdef DEBUG
	printf(" --> %lld\n", result);
#endif
	return result;
}

int main()
{
#ifdef DEBUG
	freopen("C:\\temp\\cows.txt", "r", stdin);
	freopen("C:\\temp\\result.txt", "w", stdout);
#endif
	scanf("%d", &N);

	for (int i = 1; i <= N; ++i) {
		scanf("%d", A + i);
		AMAP[A[i]] = i;			/* re-ordering */
	}

	for (int i = 1; i <= N; ++i) {
		scanf("%d", A + i);
		A[i] = AMAP[A[i]];
	}

#ifdef DEBUG
	for (int i = 1; i <= N; ++i) {
		printf("%3d", A[i]);
	}
	printf("\n");
#endif

	std::copy(A + 1, A + N + 1, B + 1);

	CROSS[0] = INVERSION(B, N);

	INT64 min_value = CROSS[0];

	for (int k = 1; k < N; ++k)
	{
		int shifted = A[k];

		CROSS[k] = CROSS[k - 1] + (N - shifted) - (shifted - 1);

		min_value = min(min_value, CROSS[k]);
	}


	printf("%lld\n", min_value);
}
